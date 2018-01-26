#include "Arduino.h"
#include "PulseGenFree.h"

PulseGenFree::PulseGenFree(int pin,unsigned int onInterval,unsigned int offInterval){
	_pin = pin;
	pinMode(_pin,OUTPUT);
	init(onInterval,offInterval);
}

void PulseGenFree::init(unsigned int onInterval,unsigned int offInterval){
	pulseOnInterval = onInterval;
	pulseOffInterval = offInterval;
		
	digitalWrite(_pin,LOW);
	pulseState = LOW;
	oldTime = micros();

}

void PulseGenFree::generator(){
	newTime = micros() - oldTime;
	
	if (pulseState == LOW && newTime >= pulseOffInterval) {
		digitalWrite(_pin,HIGH);
		pulseState = HIGH;
		
		oldTime = micros();
		
	} else if (pulseState == HIGH && newTime >= pulseOnInterval){
		digitalWrite(_pin,LOW);
		pulseState = LOW;
		
		oldTime = micros();
	}

}

