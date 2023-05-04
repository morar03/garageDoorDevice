
#include "NetworkConnection.h"


const char SeriesDevice[] = Serial_Number_Device;


const char RouteTriggerEventDoorFirebase[]= "/eventTriggerDoorFirebase";
const char RouteStatusDoorFirebase[]= "/statusDoorFirebase";
const char RouteTriggerSTOPFunctionDevice[]= "/TriggerSTOPFunctionDevice";

// WiFiManager
// Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

//Define Firebase Data object
  FirebaseData fbdo;

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void wifiConnect(void) {

  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();
  WiFi.mode(WIFI_STA);
  pinMode(LED_BUILTIN, OUTPUT);

  //Button change form AP in STA
  pinMode(APSTAbutton, INPUT_PULLUP);

  // Interrupt for change value(buttonStatus) from EEPROM
  attachInterrupt(digitalPinToInterrupt(APSTAbutton), ISRButtonDetect, FALLING); // trigger when button pressed
  int buttonStatus;
  // Get Value from EEPROM
  EEPROM.get(EEPROM_First_Value, buttonStatus); 

  if (buttonStatus == True){
    Serial.println("Button Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
    wifiManager.startConfigPortal("GarageDoor AP");
    digitalWrite(LED_BUILTIN, HIGH);
    EEPROM.put(EEPROM_First_Value, False);
    EEPROM.commit();
  }else {
    Serial.println("Button Reset NO Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    wifiManager.autoConnect("GarageDoor AP");
  }
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  // fetches ssid and pass from eeprom and tries to connect
  // wifiManager.autoConnect("AutoConnectAP");
  // wifiManager.startConfigPortal("AccesConnect2");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected to Wifi.");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Connected to Database.");
}

void InitValueDatabase(void) {
  Firebase.setBool(fbdo, ConcatRoute(SeriesDevice,RouteTriggerEventDoorFirebase), false);
  Firebase.setBool(fbdo, ConcatRoute(SeriesDevice,RouteStatusDoorFirebase), false);
  Firebase.setBool(fbdo, ConcatRoute(SeriesDevice,RouteTriggerSTOPFunctionDevice), false);
}

bool getEventDoorFirebase(void){
  Firebase.getBool(fbdo, ConcatRoute(SeriesDevice,RouteTriggerEventDoorFirebase));
  bool eventDoorFirebase = fbdo.boolData();
  return eventDoorFirebase;
}

void setEventDoorFirebase(bool eventDoorFirebase){
  Firebase.setBool(fbdo, ConcatRoute(SeriesDevice,RouteTriggerEventDoorFirebase), eventDoorFirebase);
}

bool getStatusDoorOpenClose(void){
  Firebase.getBool(fbdo, ConcatRoute(SeriesDevice,RouteStatusDoorFirebase));
  bool StatusDoorOpenClose = fbdo.boolData();
  return StatusDoorOpenClose;
}

void setStatusDoorOpenClose(bool StatusDoorOpenClose){
  Firebase.setBool(fbdo,ConcatRoute(SeriesDevice,RouteStatusDoorFirebase), StatusDoorOpenClose);
}

bool TriggerSTOPFunctionDevice(void){
  Firebase.getBool(fbdo, ConcatRoute(SeriesDevice,RouteTriggerSTOPFunctionDevice));
  bool TriggerSTOP = fbdo.boolData();
  return TriggerSTOP;
} 

char* ConcatRoute(const char* string1,const char* string2){
  static char RouteConcat[50];
   strcpy(RouteConcat, string1);
   strcat(RouteConcat, string2);
   return RouteConcat;
 }

void ICACHE_RAM_ATTR ISRButtonDetect(){
  button_time = millis();
  int buttonStatus;
  if (button_time - last_button_time > 500)
  {
    EEPROM.get(EEPROM_First_Value, buttonStatus);

    if (buttonStatus == True){
      EEPROM.put(EEPROM_First_Value, False);
      EEPROM.commit();
      ESP.restart();
    }else {
      EEPROM.put(EEPROM_First_Value, True);
      EEPROM.commit();
      ESP.restart();
    }
    last_button_time = button_time;
  }
}