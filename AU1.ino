#Alberto Chavez Rojas A01231730 4 de nov 2022 Interfaces de equipo de computo
 
#define MY_LED 3
void setup(){
  pinMode(MY_LED,OUTPUT);
  digitalWrite(MY_LED,LOW);
}
void loop(){
  digitalWrite(MY_LED,HIGH);
  delay(250);
  digitalWrite(MY_LED,LOW);
  delay(250);
}
