#ifndef StepPump_h
#define StepPump_h

#include <Arduino.h>

class StepPump {
public:

    StepPump(int pin);
	void pulseOut(int Hz);
    
private:
    int _pin;
    long newTime;
    long oldTime;
    boolean pulseState;
    int pulseTime_H;
    
};
#endif
