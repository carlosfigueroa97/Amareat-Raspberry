/*
 * Project: Amareat
 * Author: Carlos Alejandro Figueroa Bazán
 * Organization: TECNM
 */

 // IMPORT LIBRARIES
 #include <SoftwareSerial.h>

// GENERAL PRIVATE PROPERTIES
String statusDevices = "0";
String idRoom = "60a1d2445e9e790f3445d1f2";
unsigned long lastTimeMillis = 0;

// ENDPOINT PRIVATE PROPERTIES
String URL, USERNAME, PASSWORD, HEADERS;

// PIN's
const byte RX = 0;
const byte TX = 1;

// Init libraries
SoftwareSerial ESP01(RX, TX);


void setup() {
  // Init configuration
  initConfiguration();

  // Print Endpoint
  printValueOnSerial("Query Endpoint: " + URL);
  printValueOnSerial("Headers: " + HEADERS);
}

void loop() {
  if(millis() - lastTimeMillis > 30000){
    lastTimeMillis = millis();

    ESP01.println("AT+CIPMUX=1");
    delay(1000);
    checkAvailableESP01();

    ESP01.println("AT+CIPSTART=4,\"TCP\",\"amareat-dev.herokuapp.com\",80");
    delay(1000);
    checkAvailableESP01();

    String cmd = "GET /app/api/v1/devices/arduino/getDevicesByRoom?idRoom=60a1d2445e9e790f3445d1f2&status=0 HTTP/1.1";
    ESP01.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    ESP01.println(cmd);
    delay(1000);
    ESP01.println(""); 
  }

  if (ESP01.available()) {
    Serial.write(ESP01.read());
  }
}

// Methods
void initConfiguration(){
  // Init serial
  Serial.begin(9600);

  // Init ESP-01 instance
  ESP01.begin(9600);

  delay(2000);

  // Init global properties
  setGlobalValuesProperties();  
}

void printValueOnSerial(String message){
  Serial.println(message);
}

void checkAvailableESP01(){
  while(ESP01.available()){
    printValueOnSerial(ESP01.readStringUntil('\n'));
  }
}

void setGlobalValuesProperties(){
  URL = "https://amareat-dev.herokuapp.com/app/api/v1/devices/arduino/getDevicesByRoom?idRoom=60a1d2445e9e790f3445d1f2&status=0";
  USERNAME = "";
  PASSWORD = "";
  HEADERS = "GET app/api/v1/devices/arduino/getDevicesByRoom?idRoom=60a1d2445e9e790f3445d1f2&status=0 HTTP/1.0\nHost: amareat-dev.herokuapp.com\nAccept: application/json\nContent-Type: application/json\nConnection: Keep-Alive\n\n";
}
