#include <FastLED.h> // 此示例程序需要使用FastLED库

#define NUM_LEDS 64       // LED灯珠数量
#define LED_DT 6         // Arduino输出控制信号引脚
#define LED_TYPE WS2812B // LED灯带型号
#define COLOR_ORDER GRB  // RGB灯珠中红色、绿色、蓝色LED的排列顺序

uint8_t max_bright = 32; // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高

CRGB leds[NUM_LEDS]; // 建立光带leds

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS); // 初始化光带
    FastLED.setBrightness(max_bright);                              // 设置光带亮度
}

void loop()
{
    static uint8_t hue = 0;
    FastLED.showColor(CHSV(hue++, 255, 255));
    delay(100);
}
