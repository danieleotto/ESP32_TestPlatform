#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ArduinoJson.h>
#include "esp32secure.h"

#define timeInterval 5000

// Global variables
const char* SSID = SEC_SSID;
const char* PASS = SEC_PASS;
byte mac[6];
const char* ntpServer = "pool.ntp.org";
unsigned long long epochTime;
JsonDocument doc;
JsonDocument ddoc;
long int counter;
char container[256];
unsigned long stime;

// Put function declarations here:
void initWiFi();
void printMacAddress();
void checkWifiConnection();
unsigned long long getEpochTime();
void writeJson();
void readJson();

// MAIN PROGRAM
void setup() {
  // Setup code at board boot
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  delay(1000);
  Serial.println("Serial Connected!");

  counter = 0;
  
  initWiFi();
  configTime(0,0,ntpServer);
  stime = millis();
}

void loop() {
  // Put your main code here, to run repeatedly:

  if ((millis() - stime) > timeInterval){
    checkWifiConnection();
    epochTime = getEpochTime();
    Serial.print("\nEpoch Time: ");
    Serial.println(epochTime);
    if(counter>20){
      counter = 0;
    }
    counter++;

    writeJson();
    readJson();
    stime = millis();
  }
}


// Functions
void initWiFi(){
  Serial.print("\nConnecting to: ");
  Serial.println(SSID);

  WiFi.begin(SSID,PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print("-");
  }

  Serial.print("Connected to: ");
  Serial.println(SSID);
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  printMacAddress();
}


void printMacAddress(){
  WiFi.macAddress(mac);
  Serial.print("MAC Address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}


void checkWifiConnection(){
  if(WiFi.status()!=WL_CONNECTED){
    initWiFi();
  }
  //Serial.println("Reconnected.");
}


unsigned long long getEpochTime(){
  time_t now;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.print("Failed to obtain time.");
    return 0;
  }
  time(&now);
  return now;
}


void writeJson(){
  doc.clear();
  for(int i=0;i<256;i++){
    container[i] = ' ';
  }

  doc["EpochTime"] = epochTime;
  doc["TestCode"] = "12345";
  doc["Counter"] = counter;

  serializeJsonPretty(doc, Serial);
  serializeJson(doc,container);
  Serial.println("\n---END---");
}


void readJson(){

  DeserializationError error = deserializeJson(ddoc,container);
  if(error){
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    return;
  }

  unsigned long long eT = ddoc["EpochTime"];
  int n = ddoc["Counter"];
  const char* tc = ddoc["TestCode"];



  Serial.print("DES Epoch: ");
  Serial.println(eT);
  Serial.print("DES TestCode: ");
  Serial.println(tc);
  Serial.print("DES Counter: ");
  Serial.println(n);
}
