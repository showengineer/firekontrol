#include <WiFi.h>
#include <Wire.h>
#include "display.h"

bool armed = false;

Adafruit_SSD1305 display(128, 64, &Wire);
const char* ssid PROGMEM = "SCHIETKAST";
const char* pass PROGMEM = "NitraatjeErbij?";

void setupWiFi(){
  Serial.println("\n[*] Creating AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  Serial.println("[+] AP Created");
  Serial.println(WiFi.softAPIP());
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupGraphics(&armed, &display);
  setupWiFi();
  delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay();
}
