#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

#include <HTTPClient.h>
#include <Arduino.h>

class HttpManager {
public:
    HttpManager();

    // GET request
    bool getRequest(const String& url, const String& headers = "");

    // POST request
    bool postRequest(const String& url, const String& body, const String& headers = "");

    // Accessors
    String getLastRequestUrl() const { return lastRequestUrl; }
    String getLastRequestBody() const { return lastRequestBody; }
    String getLastResponse() const { return lastResponse; }
    int getLastStatusCode() const { return lastStatusCode; }

private:
    HTTPClient http;

    // Stored request/response data
    String lastRequestUrl;
    String lastRequestBody;
    String lastResponse;
    int lastStatusCode;

    void applyHeaders(const String& headers);
};

#endif
