#include <Stepper.h>

const int stepsPerRevolution = 600;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
}

void loop() {
  // step one revolution  in one direction:
  myStepper.step(100);
  delay(500);

  // step one revolution in the other direction:
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
}
