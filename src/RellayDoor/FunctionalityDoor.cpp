

#include "FunctionalityDoor.h"


void ActionDoor(){
  
   pinMode(actionDoorPin, OUTPUT);
   bool eventDoorFirebase = getEventDoorFirebase();
   Serial.print("Firebase Result: ");
   Serial.print(eventDoorFirebase);
   Serial.println('\n');
   if(eventDoorFirebase == true){
      digitalWrite(actionDoorPin, HIGH);
      Serial.print("MotorPower");
      Serial.println('\n');
      delay(2000);
      digitalWrite(actionDoorPin, LOW);
      setEventDoorFirebase(false);
    }else{
      digitalWrite(actionDoorPin, LOW);
      Serial.print("OFF");
      Serial.println('\n');
    }
}

void CheckStatusDoor(){
  pinMode(statusDoorPin, INPUT);
  int statusDoor = digitalRead(statusDoorPin);
  if (statusDoor == 0){
    Serial.println("DoorClose");
    setStatusDoorOpenClose(true);
  }else{
    Serial.println("DoorOpen");
    setStatusDoorOpenClose(false);
    delay(1000);
  }
}
