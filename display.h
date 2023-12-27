#if !defined(_FWESP_DISPLAY_H)
#define _FWESP_DISPLAY_H
#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
void setupGraphics(bool *armed, Adafruit_SSD1305 *display);
void updateDisplay();
void announceArming();
void animArmed();
void resetDisplayTimeout();

#endif
