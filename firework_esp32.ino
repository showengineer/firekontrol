#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
#include "display.h"
#include "wireless.h"
#include "api.h"
#include "fire.h"
#include "beep.h"

bool armed = false;

Adafruit_SSD1305 display(128, 64, &Wire);

WebServer* _server;

int setArmed(bool arm){
  if(arm && !armed){
    announceArming();
    outputEnable(true);
    armed = true;
    beep(200, 3, 200);
    return 0;
  }
  else if(!arm && armed){
    resetDisplayTimeout();
    outputEnable(false);
    armed = false;
    beep(1000, 1);
    return 0;
  }
  else{
    // This shouldn't be possible
    return 1;
  }
  
}

int fireChannel(int channel){
  if(!armed){
    return 1;
  }
  return fire(channel);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupGraphics(&armed, &display);
  pinMode(BEEP_PIN, OUTPUT);
  beep(200, 1);
  setupHardware();
  setupWiFi();
  _server = setupAPI(&setArmed, &fireChannel);
  delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay();
  _server->handleClient();
  //hardwareUpdate();
}
