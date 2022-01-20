#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <FastLED.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

#define NEOPIN 2
#define NUMPIXELS 60

CRGB leds[NUMPIXELS];

bool received_sat = false;
bool received_hue = false;

bool is_on = false;
float current_brightness = 20.0;
float current_sat = 0.0;
float current_hue = 0.0;
int h = 0;
int s = 0;

void setup()
{
    Serial.begin(115200);
    wifi_connect(); // in wifi_info.h

    FastLED.addLeds<WS2812B, NEOPIN, GRB>(leds, NUMPIXELS);
    delay(1000);
    my_homekit_setup();
    FastLED.setBrightness(0);
    FastLED.show();
    for (int i = 0; i < NUMPIXELS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}

void loop()
{
    my_homekit_loop();
    delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c

extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_sat;
extern "C" homekit_characteristic_t cha_hue;

static uint32_t next_heap_millis = 0;

void my_homekit_setup()
{

    cha_on.setter = set_on;
    cha_bright.setter = set_bright;
    cha_sat.setter = set_sat;
    cha_hue.setter = set_hue;

    arduino_homekit_setup(&accessory_config);
}

void my_homekit_loop()
{
    arduino_homekit_loop();
    const uint32_t t = millis();
    if (t > next_heap_millis)
    {
        // show heap info every 5 seconds
        next_heap_millis = t + 5 * 1000;
        LOG_D("Free heap: %d, HomeKit clients: %d",
              ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
    }
}

void set_on(const homekit_value_t v)
{
    bool on = v.bool_value;
    cha_on.value.bool_value = on; //sync the value
    if (on)
    {
        is_on = true;
        Serial.println("On");
    }
    else
    {
        is_on = false;
        Serial.println("Off");
    }

    updateColor();
}

void set_hue(const homekit_value_t v)
{
    Serial.println("set_hue");
    float hue = v.float_value;
    cha_hue.value.float_value = hue; //sync the value
    current_hue = hue;
    received_hue = true;

    updateColor();
}

void set_sat(const homekit_value_t v)
{
    Serial.println("set_sat");
    float sat = v.float_value;
    cha_sat.value.float_value = sat; //sync the value
    current_sat = sat;
    received_sat = true;

    updateColor();
}

void set_bright(const homekit_value_t v)
{
    Serial.println("set_bright");
    int bright = v.int_value;
    cha_bright.value.int_value = bright; //sync the value
    current_brightness = bright;

    updateColor();
}

void updateColor()
{
    if (is_on)
    {
        Serial.println("Update color");
        int v = map(current_brightness, 0, 100, 100, 255);
        if (received_hue && received_sat)
        {
            h = map(current_hue, 0, 360, 0, 255);
            s = map(current_sat, 0, 100, 0, 255);
            received_hue = false;
            received_sat = false;
        }

        FastLED.setBrightness(v);
        FastLED.show();
        Serial.println(v);
        for (int i = 0; i < NUMPIXELS; i++)
        {
            leds[i] = CHSV(h, s, v);
        }
        FastLED.show();
    }
    else if (!is_on) //lamp - switch to off
    {
        Serial.println("Turn off");
        FastLED.setBrightness(0);
        FastLED.show();
        for (int i = 0; i < NUMPIXELS; i++)
        {
            leds[i] = CRGB(0, 0, 0);
        }
        FastLED.show();
    }
}
