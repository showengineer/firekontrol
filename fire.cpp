#include "fire.h"

// Pin Defs
#define SR_OUTPUT_ENABLE D10
#define SR_SER D1
#define SR_RCLK D2
#define SR_SRCLK D3

uint16_t states;

long outputTimes[16] = {};


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
  if(channel < 1 || channel > 16){
    return 1;
  }
  states |= (1 << channel - 1);
  outputTimes[channel - 1] = millis();
  _writeState();
  return 0;
}
