#include "display.h"
#include <Arduino.h>

#include <WiFi.h>
#include <splash.h>

Adafruit_SSD1305 *_display;
bool *_armed;

long lastarmed = millis();
bool showarmed = false;
void animArmed(){
  if(millis() - lastarmed > 250){
    showarmed = !showarmed;
    lastarmed = millis();
  }

  if(showarmed){
    _display->println("    --- ARMED ---");
  }
  else
    _display->println("");
}

long displayOn;
void updateDisplay(){
  //Turn off after 60 secs, if not armed
  if(millis() - displayOn > 60000 && !_armed){
    _display->clearDisplay();
    _display->display();
    return;
  }
  _display->clearDisplay();
  _display->setTextSize(1);
  _display->setCursor(32,0);
  _display->println("FIRE SYSTEM");
  _display->setTextSize(1);
  if(!*_armed)
    _display->println("      TEST MODE");
  else
    animArmed();
  _display->print("IP: ");
  _display->println(WiFi.softAPIP());
  _display->display();
}

void setupGraphics(bool *armed, Adafruit_SSD1305 *display){
  
  if ( ! display->begin(0x3C) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  // Set as globals
  _armed = armed;
  _display = display;

  // Clear display contents
  _display->clearDisplay();
  _display->display();

  _display->setTextSize(1);
  _display->setTextColor(WHITE);
  _display->setCursor(0,0);
  _display->println("Init...");
  _display->display();
  displayOn = millis();
}
