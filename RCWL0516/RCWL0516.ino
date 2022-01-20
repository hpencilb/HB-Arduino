#define sensor 8
#define SENSOR_DELAY_TIME 20

bool input;
static uint32_t next_millis = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(sensor, INPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
    input = digitalRead(sensor);
    const uint32_t t = millis();
    if (input == HIGH)
    {   
        digitalWrite(LED_BUILTIN, HIGH);
        next_millis = t + SENSOR_DELAY_TIME * 1000;
        Serial.print("Activating...\n");
        delay(3000);
    }
    else
    {   
        if (t >= next_millis){
            digitalWrite(LED_BUILTIN, LOW);
            Serial.print("Deactivated\n");
        }
        else{
            Serial.print("Do nothing...\n");
        };
        delay(500);
    }
}
