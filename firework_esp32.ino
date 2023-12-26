#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
#include "display.h"
#include "wireless.h"
#include "api.h"

bool armed = false;

Adafruit_SSD1305 display(128, 64, &Wire);

WebServer* _server;

int setArmed(bool arm){
  if(arm && !armed){
    announceArming();
    //TODO: beep!
    armed = true;
    return 0;
  }
  else if(!arm && armed){
    //TODO: beep!
    armed = false;
    return 0;
  }
  else{
    // This shouldn't be possible
    return 1;
  }
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupGraphics(&armed, &display);
  setupWiFi();
  _server = setupAPI(&setArmed);
  delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay();
  _server->handleClient();
}
