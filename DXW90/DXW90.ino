#include <Servo.h>

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9); // attach to pin 9
}

void loop() {
  for (pos; pos < 180; pos++) {
    myservo.write(calibrate(pos));
    delay(50);
  }
  for (pos; pos > 0 ; pos--) {
    myservo.write(calibrate(pos));
    delay(50);
  }
}

int calibrate(int raw) {
  // the servo I use will hit upper limit when setting the angle to 165
  return map(raw, 0, 180, 0, 165);
}
