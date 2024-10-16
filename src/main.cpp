#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

// Global variables
const char* SSID = "";
const char* PASS = "";
byte mac[6];
const char* ntpServer = "pool.ntp.org";
unsigned long long epochTime;

// Put function declarations here:
void initWiFi();
void printMacAddress();
void checkWifiConnection();
unsigned long long getEpochTime();


// MAIN PROGRAM
void setup() {
  // Setup code at board boot
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  delay(1000);
  Serial.println("Serial Connected!");
  
  initWiFi();
  configTime(0,0,ntpServer);
}

void loop() {
  // Put your main code here, to run repeatedly:
  checkWifiConnection();

  epochTime = getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  delay(5000);
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
  Serial.println("Reconnected.");
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
