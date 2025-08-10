#ifndef WIFI_MANAGER_H  
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager {
    public:
        WiFiManager(const char* ssid, const char* password);
        void connect();
        void addEvents();

    private:
        const char* _ssid;
        const char* _password;
        void handleDisconnectEvent(WiFiEvent_t event, WiFiEventInfo_t info);
        void handleNotConnectedConnectionStatus();
};

#endif