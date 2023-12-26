#include <WiFi.h>
#include <Wire.h>
#include "display.h"
#include "wireless.h"

bool armed = false;

Adafruit_SSD1305 display(128, 64, &Wire);

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
