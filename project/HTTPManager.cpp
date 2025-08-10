#include "HttpManager/HttpManager.h"

HttpManager::HttpManager() 
    : lastRequestUrl(""), lastRequestBody(""), lastResponse(""), lastStatusCode(0) {}

bool HttpManager::getRequest(const String& url, const String& headers) {
    lastRequestUrl = url;
    lastRequestBody = ""; // GET has no body

    http.begin(url);
    applyHeaders(headers);

    lastStatusCode = http.GET();

    if (lastStatusCode > 0) {
        lastResponse = http.getString();
        http.end();
        return true;
    } else {
        lastResponse = http.errorToString(lastStatusCode);
        http.end();
        return false;
    }
}

bool HttpManager::postRequest(const String& url, const String& body, const String& headers) {
    lastRequestUrl = url;
    lastRequestBody = body;

    http.begin(url);
    applyHeaders(headers);

    lastStatusCode = http.POST(body);

    if (lastStatusCode > 0) {
        lastResponse = http.getString();
        http.end();
        return true;
    } else {
        lastResponse = http.errorToString(lastStatusCode);
        http.end();
        return false;
    }
}

void HttpManager::applyHeaders(const String& headers) {
    if (headers.length() == 0) return;

    // Expected format: "Header1: value1\nHeader2: value2"
    int start = 0;
    while (start < headers.length()) {
        int end = headers.indexOf('\n', start);
        if (end == -1) end = headers.length();

        String line = headers.substring(start, end);
        int sep = line.indexOf(':');
        if (sep > 0) {
            String key = line.substring(0, sep);
            String value = line.substring(sep + 1);
            key.trim();
            value.trim();
            http.addHeader(key, value);
        }
        start = end + 1;
    }
}
