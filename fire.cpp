#include "fire.h"

// Pin Defs
#define SR_OUTPUT_ENABLE 10
#define SR_SER 3
#define SR_RCLK 4
#define SR_SRCLK 5

#define CUE_COUNT 16
#define CUE_HOLDING_TIME 1000
#define CUE_HOLD 3
uint16_t states;
uint8_t hold;
unsigned long outputTimes[CUE_COUNT] = {0};


void _writeState(){
  digitalWrite(SR_RCLK, LOW);
  shiftOut(SR_SER, SR_SRCLK, LSBFIRST, states);
  shiftOut(SR_SER, SR_SRCLK, LSBFIRST, (states >> 8));
  digitalWrite(SR_RCLK, HIGH);
}

void setupHardware(){
  pinMode(SR_OUTPUT_ENABLE, OUTPUT);
  pinMode(SR_SER, OUTPUT);
  pinMode(SR_RCLK, OUTPUT);
  pinMode(SR_SRCLK, OUTPUT);
  states = 0;
  hold = 0;
  _writeState();
}

void outputEnable(bool enable){
  // Clear shift regs before arming/enabling to prevent accidental firing.
  states = 0;
  _writeState();
  
  digitalWrite(SR_OUTPUT_ENABLE, !enable);
}

int fire(uint8_t channel){
  // Dit kan nie he
  if(channel < 1 || channel > CUE_COUNT){
    return 1;
  }
  // Lol dit is puur omdat hardwareUpdate() niet werkt
  if(hold > CUE_HOLD){
    states = 0;
    _writeState();
    hold = 0;
  }
  states |= (1 << channel - 1);
  outputTimes[channel - 1] = millis();
  _writeState();
  hold++;
  return 0;
}

void hardwareUpdate(){
  // Check if outputs have been up longer for CUE_HOLDING_TIME ms. If so, turn them off.
  unsigned long cur = millis();
  for(uint8_t i = 0; i < CUE_COUNT; i++){
    if(cur - outputTimes[i] > CUE_HOLDING_TIME){
      states &= (1 << i);
    }
  }
  _writeState();
}
