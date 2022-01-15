#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__)
#define servo_pin 2

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600, 60000);
Servo myservo;

void setup()
{
    myservo.attach(servo_pin, 500, 2500); // I have a SG90, have to attach like this
    Serial.begin(115200);
    wifi_connect(); // in wifi_info.h
    //homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example
    my_homekit_setup();
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
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_manual_on;
extern "C" homekit_characteristic_t cha_timer_on;

static uint32_t next_heap_millis = 0;
bool timer_set_off = false;
bool timer_is_on = true;
bool manual_is_on = false;

//Called when the switch value is changed by iOS Home APP
void cha_manual_on_setter(const homekit_value_t value)
{
    bool on = value.bool_value;
    cha_manual_on.value.bool_value = on; //sync the value
    LOG_D("manual: %s", on ? "ON" : "OFF");
    if (on)
    {
        set_off();
        cha_manual_on.value.bool_value = !on;
        homekit_characteristic_notify(&cha_manual_on, cha_manual_on.value);
    }
}

void cha_timer_on_setter(const homekit_value_t value)
{
    bool on = value.bool_value;
    cha_timer_on.value.bool_value = on; //sync the value
    LOG_D("timer: %s", on ? "ON" : "OFF");
    timer_is_on = on;
}

void my_homekit_setup()
{

    timeClient.begin();

    cha_manual_on.setter = cha_manual_on_setter;
    cha_timer_on.setter = cha_timer_on_setter;
    arduino_homekit_setup(&config);

    //report the switch value to HomeKit if it is changed (e.g. by a physical button)
    cha_timer_on.value.bool_value = timer_is_on;
    cha_manual_on.value.bool_value = manual_is_on;
    homekit_characteristic_notify(&cha_timer_on, cha_timer_on.value);
    homekit_characteristic_notify(&cha_manual_on, cha_manual_on.value);
}

void my_homekit_loop()
{
    arduino_homekit_loop();
    const uint32_t t = millis();
    if (t > next_heap_millis)
    {
        // show heap info every 5 seconds
        next_heap_millis = t + 5 * 1000;
        LOG_D("Free heap: %d, HomeKit clients: %d", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
        timeClient.update();
        int hr = timeClient.getHours();
        int mi = timeClient.getMinutes();
        if ((hr == 18) && ((mi == 30) || (mi == 35)))
        {
            if (timer_is_on && !timer_set_off)
            {
                set_off();
                timer_set_off = true;
            }
        }
        else
        {
            myservo.write(calibrate(90));
            timer_set_off = false;
            LOG_D("Not time yet");
        }
    }
}

int calibrate(int raw)
{
    // the servo I use will hit upper limit when setting the angle to 165
    return map(raw, 0, 180, 0, 165);
}

void set_off()
{
    myservo.write(calibrate(25));
    delay(500);
    myservo.write(calibrate(90));
    LOG_D("Set off once");
}
