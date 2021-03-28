#define LED 12
#define sensor 8

bool input;

void setup(){
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  input = digitalRead(sensor);
  Serial.println("Raw Value :");
  Serial.print(input);
  Serial.println(input ? "+HIGH" : "-LOW");
  if (input == HIGH){
    digitalWrite(LED, HIGH);
    delay(5);
    digitalWrite(LED, LOW);
  }else delay(1);
}
