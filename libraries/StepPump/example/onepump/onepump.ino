#include "StepPump.h"
StepPump PumpA(3);
#define dir 4
#define Vin 5

void setup(){
	pinMode(dir, OUTPUT);
	pinMode(Vin, OUTPUT);
}


void loop(){
	/*  digitalWrite(Vin, 0);
	digitalWrite(dir, 0);*/
	PumpA.pulseOut(1016); //15.6E-6 * INPUT - (1 - 601.2E-6)* INPUT + OUTPUT = 0, target_Hz = Output, 计算出对应的Input
}