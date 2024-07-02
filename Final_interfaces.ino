//Final Interfaces
/*
 * Alberto Chavez Rojas       A01231730
 * Daniel De La Torre Chapell A01733400
 * Sebastian Llanos Arroyo    A01731093
 */

#include <USB.h>                  // required library for chipKIT USB functionspin
#define INTERNAL_BUTTON  18       // Board button's pin
#define echoPin 11 
#define trigPin 12
#define ResPin A1


USBFS      usbDriver;             // Full-Speed definition object (12 Mbps)
USBManager USB(usbDriver,         // driver type      | Full-Speed (12 Mbps)
               0x1209,            // Vendor ID (VID)  | 0x1209 = Generic VID
               0x2600,            // Product ID (PID) | 0x2600 = Majenko Tech.
               "MY BRAND NAME",   // Manufacture's name
               "MY PRODUCT NAME", // Product's name
               "01234");          // serial number (optional parameter)

HID_Keyboard  usbKeyboard;        // Human Interface Device class - Keyboard subclass

bool buttonStatus = true;         // boolean variable to store button status
bool CamOn = false;
bool ChatOn = false;

// defines variables
long duration; 
int d;

//////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  USB.addDevice(usbKeyboard);      // Add HID's keyboard to USB descriptor
  USB.begin();                     // initialize USB descriptor devices
  pinMode(INTERNAL_BUTTON, INPUT); // Button's pin as input
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  //MIC
  buttonStatus = digitalRead(INTERNAL_BUTTON); // Read and store button status
  if(buttonStatus == false){
    delay(10);                               // Wait time to debounce button

    usbKeyboard.pressRawModifier(KEY_RAW_MOD_LALT);
    usbKeyboard.pressRaw(KEY_RAW_A);
    usbKeyboard.releaseRaw(KEY_RAW_A);
    usbKeyboard.releaseRawModifier(KEY_RAW_MOD_LALT);
    delay(10);
    while(digitalRead(INTERNAL_BUTTON) == false); 
  }
////////////////////////////////////////////////////////////////////////////////
  //CHAT
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  d = duration * 0.034 / 2;//calculaos distancia
  
  if(ChatOn == false){ // Variable de control para chat y ultrasonico
    if(d>0 && d<=15){
      usbKeyboard.pressRawModifier(KEY_RAW_MOD_LALT);
      usbKeyboard.pressRaw(KEY_RAW_H);
      usbKeyboard.releaseRaw(KEY_RAW_H);
     usbKeyboard.releaseRawModifier(KEY_RAW_MOD_LALT);
      ChatOn = true;
      delay(10);
    }
  }
  if(d>35){
    ChatOn=false;
  }
////////////////////////////////////////////////////////////////////////////////
  //CAMERA
  int light = analogRead(ResPin);
  Serial.println(light);
  if(CamOn == false){ // Variable de control para fotoresistencia y activar microfono
    if(light >= 1023){
      usbKeyboard.pressRawModifier(KEY_RAW_MOD_LALT);
      usbKeyboard.pressRaw(KEY_RAW_V);
      usbKeyboard.releaseRaw(KEY_RAW_V);
      usbKeyboard.releaseRawModifier(KEY_RAW_MOD_LALT);
      CamOn = true;
      delay(10);
    }
  }
  if(light<800){
    CamOn=false;
  } 
}
