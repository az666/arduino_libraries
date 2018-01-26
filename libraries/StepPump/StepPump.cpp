
#include "StepPump.h"

StepPump::StepPump(int pin)
{
  DDRD = 1 << pin | B0000000;
  _pin = pin;
}

void StepPump::pulseOut(int Hz) // 15.6E-6 * INPUT -(1-601.2E-6)* INPUT + OUTPUT = 0, target_Hz = Output, 计算出对应的Input
{
  newTime = micros() - oldTime;
  pulseTime_H = 500000  / Hz; 
  if (newTime >= pulseTime_H){
	  pulseState = !pulseState;
	  PORTD = pulseState << _pin | B0000000;
	  oldTime = micros();
  }
}





