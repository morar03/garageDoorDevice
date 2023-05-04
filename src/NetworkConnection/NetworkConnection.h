
#include <Arduino.h>

// Include the Wi-Fi library
#include <ESP8266WiFi.h>

// Include the library for change AP to STM
#include <WiFiManager.h>

// Include the Firebase library      
#include <FirebaseESP8266.h>

// Include the EEPROM library for access to non-volatile memory
#include <EEPROM.h>


// THE SECRET CREDETIALS
#include "envCredentials.h"

// THE SECRET CREDETIALS

// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 1

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

// Digital Pin to operate the door
#define actionDoorPin D1

// Size allocation for the value in EEPROM
#define EEPROM_SIZE 1

// Address start for the value in EEPROM
#define EEPROM_First_Value 0

//Defined Digital Pin for the button of change form AP in STA 
#define APSTAbutton D6

//Defined True and False with 1 and 0 
#define True 1
#define False 0



void wifiConnect(void);
void InitValueDatabase(void);
bool getEventDoorFirebase(void);
void setEventDoorFirebase(bool eventDoorFirebase);
bool getStatusDoorOpenClose(void);
void setStatusDoorOpenClose(bool DoorOpenClose);
void ISRButtonDetect();
char* ConcatRoute(const char string1[],const char string2[]);
bool TriggerSTOPFunctionDevice(void);