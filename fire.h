#if !defined(_FWESP_FIRE_H)
#define _FWESP_FIRE_H
#include <Arduino.h>
void setupHardware();
void outputEnable(bool enable);
int fire(uint8_t channel);
void hardwareUpdate();
#endif
