#include "api.h"
#include <Arduino.h>

#include <uri/UriBraces.h>

WebServer server(80); 

int (*doArm)(bool);
int (*doFire)(int);

void handleRoot(){
  server.send(200, "text/plain", "Firework ignition system, 16 channels");
}

void handleArm(){
  if(!(*doArm)(true)){
    server.send(200, "text/plain", "System armed!");
  }
  else{
    server.send(400, "text/plain", "System already armed");
  }
}

void handleDisarm(){
  if(!(*doArm)(false)){
    server.send(200, "text/plain", "System disarmed!");
  }
  else{
    server.send(400, "text/plain", "System already disarmed");
  }
}


WebServer *setupAPI(int (*armHandle)(bool), int (*fireHandle)(int)){
  doArm = armHandle;
  doFire = fireHandle;
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/reset", handleDisarm);
  
  server.on(UriBraces("/fire/{}"), []() {
    String input = server.pathArg(0);
    int channel = input.toInt();

    if(channel < 1 || channel > 16){
      server.send(400, "text/plain", "Channel input invalid");
    }
    if(!(*doFire)(channel)){
      server.send(200, "text/plain", "Fired channel " + input);
    }
    else{
      server.send(400, "text/plain", "Failed to fire channel " + input + "");
    }
    
  });
  
  server.begin();

  return &server;
}
