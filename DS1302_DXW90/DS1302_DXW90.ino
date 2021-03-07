#include <stdio.h>
#include <DS1302.h>
#include <Servo.h>

const int kCePin   = 7;  // Chip Enable // RST
const int kIoPin   = 6;  // Input/Output // DAT
const int kSclkPin = 5;  // Serial Clock // CLK
const int buttonPin = 0;
DS1302 rtc(kCePin, kIoPin, kSclkPin);
Servo myservo;
int buttonState = 0;

void setup() {
//  Serial.begin(9600);
  myservo.attach(8); // attach to pin 9
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Time t = rtc.time();
  if((t.hr==18)&&(t.min==30)){
    set_off();
  } else myservo.write(calibrate(90));
//  Serial.println(t.min);
//  Serial.println(t.sec);
  delay(1000);
  if (buttonState == LOW) {
    set_off();
  } 
}

void set_time(Time t){
  rtc.writeProtect(false);
  rtc.halt(false);
  rtc.time(t);
}


int calibrate(int raw) {
  // the servo I use will hit upper limit when setting the angle to 165
  return map(raw, 0, 180, 0, 165);
}

void set_off(){
  myservo.write(calibrate(35));
  delay(1000);
  myservo.write(calibrate(90));  
}
