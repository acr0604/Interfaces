//ALberto Chavez Rojas
//A01231730
//Interfaces de equipo de computo
//11 de nov 2022

int analogpin = A0;
int sensorValue=0;

void setup()
{
  
  Serial.begin(9600);
  delay(5000); // give some time to create virtual
               // serial port before loop() begins
}

void loop()
{
  sensorValue = analogRead(analogpin);
  Serial.write(sensorValue/4); // sends a raw byte
  delay(100);
}
