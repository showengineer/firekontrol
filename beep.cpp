#include "beep.h"
#include <Arduino.h>
void beep(int duration, int times, int off_duration){
  for(int i = 0; i < times; i++){
    digitalWrite(BEEP_PIN, HIGH);
    delay(duration);
    digitalWrite(BEEP_PIN, LOW);
    delay(off_duration);
  }
}
