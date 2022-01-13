void setup()
{
    pinMode(14, OUTPUT);
    analogWriteFreq(200);
    analogWriteRange(1000);
}

int value = 0;

void loop()
{
    for (value; value < 1000; value = value + 10)
    {
        analogWrite(14, value);
        delay(500);
    }
    for (value; value > 0; value = value - 10)
    {
        analogWrite(14, value);
        delay(500);
    }
}
