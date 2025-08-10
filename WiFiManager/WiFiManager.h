#ifndef WIFI_MANAGER_H  
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager {
    public:
        WiFiManager(const char* ssid, const char* password);
        void connect();
        void handleNotConnectedConnectionStatus();
        void addEvents();

    private:
        const char* _ssid;
        const char* _password;
        void handleDisconnectEvent(WiFiEvent event, WiFiEventInfo info);
        void handleNotConnectedConnectionStatus();
}

#endif