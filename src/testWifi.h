/*
    Test for moving al WiFi related procedures inside a separate file
*/

#ifndef testWifi_h
#define testWifi_h

#include "Arduino.h"

class WifiConnection {
    public:
        WifiConnection(const char* SSID, const char* PASS);
        void connect();
        void checkConnection();
        void printMacAddress();
    private:
        const char* _SSID;
        const char* _PASS;
        byte mac[6];
};

#endif