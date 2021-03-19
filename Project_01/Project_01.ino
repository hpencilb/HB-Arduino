#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
#include <Servo.h>

#define Trig 6
#define Echo 7
#define Serv 8
#define X_stick A2
#define Y_stick A3
#define Z_btn 2

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows

float distance, temp;

int pos = 90;

int x, y, z;
int x_bias = 508;
int y_bias = 531;

void setup() {
  lcd.init();                        // Initialize I2C LCD module
  lcd.backlight();                   // Turn backlight ON
  myservo.attach(Serv);
  myservo.write(90);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Z_btn, INPUT_PULLUP); 
  digitalWrite(Z_btn, HIGH);
}

void loop() {
  lcd.clear();
  measure_distance();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");
  x = -(analogRead(X_stick) - x_bias); 
  y = analogRead(Y_stick) - y_bias; 
  calibrate_x_y();
  if(!(abs(x) < 5)){
    if(x < 0){
      pos += 5;
    }else{
      pos -= 5;
    } 
  }
  if(pos < 30) pos = 30;
  if(pos > 170) pos = 170;
  myservo.write(pos);
  lcd.setCursor(0, 1);
  lcd.print(pos); 
  if(digitalRead(Z_btn) != 1){
    pos = 90;
    myservo.write(pos);
  }
  
  delay(250);
}

void measure_distance(){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  temp = float(pulseIn(Echo, HIGH));
  distance = (temp * 17 )/1000;
}

void calibrate_x_y(){
  if(x>=0){
    x = map(x, 0, 1023-x_bias, 0, 511);  
  } else{
    x = map(x, -x_bias, 0, -512, 0);
  }
  if(y>=0){
    y = map(y, 0, 1023-y_bias, 0, 511);  
  } else{
    y = map(y, -y_bias, 0, -512, 0);
  }
}
