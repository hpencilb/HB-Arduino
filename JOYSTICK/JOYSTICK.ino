int value = 0; 
void setup() { 
 pinMode(2, INPUT); 
 digitalWrite(2, HIGH);
 Serial.begin(9600); 
} 
void loop() { 
 value = analogRead(A4); 
 Serial.print("X:"); 
 Serial.print(value, DEC); 
 value = analogRead(A5); 
 Serial.print(" | Y:"); 
 Serial.print(value, DEC); 
 value = digitalRead(2); 
 Serial.print(" | Z: "); 
 Serial.println(value); 
 delay(100); 
} 
