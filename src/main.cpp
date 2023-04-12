

#include <Arduino.h>
 
#include "./RellayDoor/FunctionalityDoor.h"

#include "./NetworkConnection/NetworkConnection.h"


void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  wifiConnect();
  InitValueDatabase();
}

void loop() {
  if (TriggerSTOPFunctionDevice() == False){
    ActionDoor();
    CheckStatusDoor();
  }
}
