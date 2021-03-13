#define pin_G 3
#define pin_R 5
#define pin_B 6

int R, G, B;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_G, OUTPUT);
  pinMode(pin_R, OUTPUT);
  pinMode(pin_B, OUTPUT);
  analogWrite(pin_G, 255);
  analogWrite(pin_R, 255);
  analogWrite(pin_B, 255);
}

void loop() {
  R = random(0, 256);
  G = random(0, 256);
  B = random(0, 256);
  analogWrite(pin_R, R);
  analogWrite(pin_G, G);
  analogWrite(pin_B, B);
  delay(1000);
}
