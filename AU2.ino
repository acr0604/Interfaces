//Alberto Chavez Rojas
//A01231730
//22 nov 2022
//Interfaces de equipo de cómputo

#define MY_BUTTON 18

bool buttonStatus = true;

void setup()
{
  Serial.begin(9600);
  pinMode(MY_BUTTON, INPUT);
}

void loop()
{
  do
  {
    buttonStatus = digitalRead(MY_BUTTON);
  } while(buttonStatus == true); // button is not pressed
   delay(10); // button was pressed, wait for bounce
  do
  {
    buttonStatus = digitalRead(MY_BUTTON);
  } while(buttonStatus == false); // button is not released
   delay(10); // button war released, wait for bounce

  Serial.println("Push button pressed and released...");
  delay(10);
}
