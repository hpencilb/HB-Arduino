#include <LedControl.h>

int DIN = 7;
int CS = 6;
int CLK = 5;

int smalllove[8][8] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 1, 0, 0, 1, 0, 0, 
    0, 1, 1, 1, 1, 1, 1, 0, 
    0, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 1, 1, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
};

LedControl lc = LedControl(DIN, CLK, CS);

void setup() {
  lc.shutdown(0, false); //启动时，MAX72XX处于省电模式
  lc.setIntensity(0, 1); //将亮度设置为最大值
  lc.clearDisplay(0);    //清除显示
}

void loop() {
  Display(smalllove);
  delay(1000);
}

void Display(int input[8][8]) {
  byte output[8];
  for (int i = 0; i < 8; i++) {
    int temp = 0;
    for (int j = 0; j < 8; j++) {
      temp = (temp << 1) + input[i][j];
    }
    lc.setRow(0, i, ~(byte)temp);
  }
}
