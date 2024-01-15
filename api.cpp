#include "api.h"
#include <Arduino.h>

#include <uri/UriBraces.h>

WebServer server(80); 

int (*doArm)(bool);
int (*doFire)(int);

void handleRoot(){
  char temp[3900];
  snprintf(temp, 3900, "<!DOCTYPE html><html lang=en><meta charset=UTF-8><meta author=\"Hugo Woesthuis, code portions generated by ChatGPT\"><meta content=\"width=device-width,initial-scale=1\"name=viewport><title>Fire Control Panel</title><style>.button-grid{display:grid;grid-template-columns:repeat(4,1fr);gap:5px;margin:20px}.button{width:calc(100% - 10px);height:100px;padding:10px;font-size:16px;text-align:center;color:#fff;border:none;background-color:#e74c3c;cursor:pointer}.red-button{background-color:#e74c3c}.green-button{background-color:#2ecc71}.blue-button{background-color:#3498db}</style><button class=red-button onclick=armSystem() id=armButton>Arm</button> <button class=\"red-button blue-button\"onclick=disarmSystem()>Disarm</button><h1>Fire Control</h1><div class=button-grid><button class=button onclick=sendRequest(1)>Fire 1</button> <button class=button onclick=sendRequest(2)>Fire 2</button> <button class=button onclick=sendRequest(3)>Fire 3</button> <button class=button onclick=sendRequest(4)>Fire 4</button> <button class=button onclick=sendRequest(5)>Fire 5</button> <button class=button onclick=sendRequest(6)>Fire 6</button> <button class=button onclick=sendRequest(7)>Fire 7</button> <button class=button onclick=sendRequest(8)>Fire 8</button> <button class=button onclick=sendRequest(9)>Fire 9</button> <button class=button onclick=sendRequest(10)>Fire 10</button> <button class=button onclick=sendRequest(11)>Fire 11</button> <button class=button onclick=sendRequest(12)>Fire 12</button> <button class=button onclick=sendRequest(13)>Fire 13</button> <button class=button onclick=sendRequest(14)>Fire 14</button> <button class=button onclick=sendRequest(15)>Fire 15</button> <button class=button onclick=sendRequest(16)>Fire 16</button></div><h2>Effects</h2><div>Fire cue <input id=minCue max=16 style=width:40px type=number min=1> to <input id=maxCue max=16 style=width:40px type=number min=1> with <input id=interval max=5 style=width:45px type=number step=.01> seconds per cue inteval. <button class=red-button onclick=intervalEffect()>Fire effect</button></div><script>function sleep(ms){return new Promise(resolve=>setTimeout(resolve,ms))}async function intervalEffect(){let mi=Number(document.getElementById('minCue').value);let ma=Number(document.getElementById('maxCue').value);let inv=Number(document.getElementById('interval').value);if(mi>=ma){alert(\"Maximum is higher than the minimum!\");return}for(let i=mi;i<=ma;i+=1){fetch(`/fire/${ i }`,{method:'GET'}).then(response=>{if(!response.ok){throw new Error('Network response was not ok')}console.log(`Fire command sent for button ${ number }`)}).catch(error=>{console.error('There was a problem with the fetch operation:',error)});await sleep(inv*1000)}}function sendRequest(number){fetch(`/fire/${ number }`,{method:'GET'}).then(response=>{if(!response.ok){throw new Error('Network response was not ok')}console.log(`Fire command sent for button ${ number }`)}).catch(error=>{console.error('There was a problem with the fetch operation:',error)})}function armSystem(){fetch('/arm',{method:'GET'}).then(response=>{if(!response.ok){throw new Error('Network response was not ok')}document.getElementById('armButton').classList.add('green-button');document.getElementById('armButton').classList.remove('red-button');const buttons=document.querySelectorAll('.button');buttons.forEach(button=>{button.disabled=false})}).catch(error=>{console.error('There was a problem with the arm request:',error)})}function disarmSystem(){fetch('/reset',{method:'GET'}).then(response=>{if(!response.ok){throw new Error('Network response was not ok')}document.getElementById('armButton').classList.remove('green-button');document.getElementById('armButton').classList.add('red-button')}).catch(error=>{console.error('There was a problem with the disarm request:',error)})}</script>");
  server.send(200, "text/html", temp);
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
