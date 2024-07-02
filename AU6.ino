//ALberto Chavez Rojas
//A01231730
//Interfaces de equipo de computo
//22 de nov 20223+

/* 
 *  For a complete USB functions and definitions reference, consult:
 *  https://github.com/chipKIT32/chipKIT-core/blob/master/pic32/cores/pic32/USB.h 
 */ 

#include <USB.h>                  // required library for chipKIT USB functions
#define INTERNAL_LED      3       // Board LED's pin
#define INTERNAL_BUTTON  18       // Board button's pin

USBFS      usbDriver;             // Full-Speed definition object (12 Mbps)
USBManager USB(usbDriver,         // driver type      | Full-Speed (12 Mbps)
               0x1209,            // Vendor ID (VID)  | 0x1209 = Generic VID
               0x2600,            // Product ID (PID) | 0x2600 = Majenko Tech.
               "MY BRAND NAME",   // Manufacture's name
               "MY PRODUCT NAME", // Product's name
               "01234");          // serial number (optional parameter)

HID_Keyboard  usbKeyboard;        // Human Interface Device class - Keyboard subclass

bool buttonStatus = true;         // boolean variable to store button status

void setup()
{
  USB.addDevice(usbKeyboard);      // Add HID's keyboard to USB descriptor
  USB.begin();                     // initialize USB descriptor devices
  pinMode(INTERNAL_LED, OUTPUT);   // LED's pin as output
  digitalWrite(INTERNAL_LED, LOW); // Turn off LED at the beginning
  pinMode(INTERNAL_BUTTON, INPUT); // Button's pin as input
}

void loop()
{
  buttonStatus = digitalRead(INTERNAL_BUTTON); // Read and store button status
  if(buttonStatus == false)                    // Button is pressed? If so...
  {
      digitalWrite(INTERNAL_LED, HIGH);        // LED monitor ON
      delay(10);                               // Wait time to debounce button

      usbKeyboard.pressRawModifier(KEY_RAW_MOD_LALT);
      usbKeyboard.pressRaw(KEY_RAW_TAB);
      usbKeyboard.releaseRaw(KEY_RAW_TAB);
      usbKeyboard.releaseRawModifier(KEY_RAW_MOD_LALT);

      while(digitalRead(INTERNAL_BUTTON) == false); // Button still pressed? Repeat until released
      delay(10);                                    // Wait time to debounce button 
      digitalWrite(INTERNAL_LED, LOW);              // LED monitor OFF
  }
}
