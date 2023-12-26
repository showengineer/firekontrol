#include "api.h"
#include <Arduino.h>

WebServer server(80); 

int (*doArm)(bool);

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

WebServer *setupAPI(int (*armHandle)(bool)){
  doArm = armHandle;
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/reset", handleDisarm);

  server.begin();

  return &server;
}
