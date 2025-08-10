#include <WiFi.h>
#include "WiFiManager/WiFiManager.h"

WiFiManager* globalWiFiManager = nullptr;

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : _ssid(ssid), _password(password) {}

void WiFiManager::connect() {
    Serial.print("Connecting to WiFi");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        handleNotConnectedConnectionStatus();
    }

    Serial.println();
    Serial.println("###################################################################");
    Serial.println("Connected to WiFi!");
    Serial.println("###################################################################");
}


void handleWiFiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    if (globalWiFiManager) {
        globalWiFiManager->connect();
    }
}

void WiFiManager::addEvents() {
    globalWiFiManager = this;
    WiFi.onEvent(handleWiFiDisconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
}

void WiFiManager::handleNotConnectedConnectionStatus() {
    if(WiFi.status() == WL_CONNECT_FAILED) {
        Serial.println("### Connection failed! Retrying...");
    }else if(WiFi.status() == WL_NO_SSID_AVAIL) {
        Serial.println("### SSID not available! Please check your credentials.");
    }else if(WiFi.status() == WL_IDLE_STATUS) {
        Serial.println("### Idle status, waiting to connect...");
    } else if(WiFi.status() == WL_DISCONNECTED) {
        Serial.println("### Disconnected! Attempting to reconnect...");
    } else {
        Serial.print("### An unexpected status occurred: " + String(WiFi.status()));
    }
}