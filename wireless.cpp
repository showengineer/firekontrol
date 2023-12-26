#include "wireless.h"
#include <Arduino.h>
#include <WiFi.h>

const char* ssid PROGMEM = "SCHIETKAST";
const char* pass PROGMEM = "NitraatjeErbij?";

void setupWiFi(){
  Serial.println("\n[*] Creating AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  Serial.println("[+] AP Created");
  Serial.println(WiFi.softAPIP());
}
