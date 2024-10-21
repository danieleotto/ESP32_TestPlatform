#include "Arduino.h"
#include "testWifi.h"
#include <WiFi.h>

WifiConnection::WifiConnection(const char* SSID, const char* PASS){
    _SSID = SSID;
    _PASS = PASS;
}

void WifiConnection::connect(){
    Serial.print("\nConnecting to: ");
    Serial.println(_SSID);

    WiFi.begin(_SSID,_PASS);

    while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print("-");
    }

    Serial.print("Connected to: ");
    Serial.println(_SSID);
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    this->printMacAddress();
}

void WifiConnection::checkConnection(){
    if(WiFi.status()!=WL_CONNECTED){
        this->connect();
    }
}

void WifiConnection::printMacAddress(){
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