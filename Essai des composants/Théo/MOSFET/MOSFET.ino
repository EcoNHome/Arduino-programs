#define MOSFETport 6;

void setup()
{
    Serial.begin(9600);
    pinMode(MOSFETport, OUTPUT);
}

void loop()
{
    for(int i=0; i<1024; i++)
    {
        analogWrite(MOSFETport, i);
        delay(200);
    }

    for(int i=1023 ; i>=0; i--)
    {
        analogWrite(MOSFETport, i);
        delay(200);
    }
}
