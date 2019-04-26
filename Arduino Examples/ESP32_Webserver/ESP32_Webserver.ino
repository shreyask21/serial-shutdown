/*
 * ESP32 Webserver with SPIFFS and WiFi AP mode
 * By Shreyas K
 */

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#define PasswordProtectAP true; //Comment out if you do not want password for AP.

const char* keyword = "Hello";
const char* ssid = "ESP32_WebServer"; //Webserver AP SSID
const char* password = "password"; //Webserver AP Password

AsyncWebServer server(80); //Start Async Webserver on port 80.

void setup() {
  Serial.begin(9600);
  #ifdef PasswordProtectAP
  WiFi.softAP(ssid, password); //Use password protected AP
  #else
  WiFi.softAP(ssid); //Use open AP
  #endif
  
  SPIFFS.begin(); //Begin the SPIFFS
  server.begin(); //Begin Webserver
  
  //Return MIME types as per HTTP requests:
   server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html","text/html");
  });
  server.on("/WindowsClient.exe", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/WindowsClient.exe","application/octet-stream");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.print(keyword);
    delay(300);
    Serial.print(keyword);
    delay(300);
    Serial.print(keyword); //Send keyword thrice just for good measure :D
    request->send(SPIFFS, "/index.html","text/html");
  });
}
void loop() {
}
