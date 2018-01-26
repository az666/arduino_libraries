#include <Arduino.h>
#include "DotMatrix.h"
 
class LEDScreenHelper {
public:
    LEDScreenHelper(const int WIDTH=32,
            const int A=2,const int B=3,const int CLK=12,
            const int STB=10,const int R=11,const int OE=9):
            HEIGHT(16),WIDTH(WIDTH),A(A),B(B),SHCP(CLK),STCP(STB),DS(R),OE(OE){}
     
    void setup(){
        pinMode(A,OUTPUT);
        pinMode(B,OUTPUT);
        pinMode(STCP,OUTPUT);
        pinMode(SHCP,OUTPUT);
        pinMode(DS,OUTPUT);
        pinMode(OE,OUTPUT);
    }
     
    void setRow(byte row){
        digitalWrite(A,row&0x01);
        digitalWrite(B,row&0x02);
    }
     
    void sendColData(byte data){
        for(int i = 0;i<8;++i){
            digitalWrite(DS,(data&0x80));
            data<<=1;
            digitalWrite(SHCP,0);
            digitalWrite(SHCP,1);
        }
    }
     
    void setOE(bool enable){
        digitalWrite(OE, enable);
    }
     
    void display(DotMatrix &data){
        for(int row = 0;row<4;++row){
            digitalWrite(OE,0);
            for(int col = 0;col<WIDTH/2;++col){
                byte val = data.get((12-((col&3)<<2)+row),(col>>2));
                sendColData(~val);
            }
            setRow(row);
            digitalWrite(STCP,0);
            digitalWrite(STCP,1);
            digitalWrite(OE,1);
        }
        digitalWrite(OE,0);
    }
     
private:
    const int HEIGHT,WIDTH;
    const int A,B,SHCP,STCP,DS,OE;
};