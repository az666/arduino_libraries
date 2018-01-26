#include "DS18B20_S.h"
//DS18B20(byte pin)  连接管脚
//传感器设定为10位模式，每次转换时间<187.5ms,如果需要12位模式，请修改库文件of ds.set(0x7F);
DS18B20_S  ds(9);//pin9
void setup() {
  Serial.begin(9600);
}
void loop() { 
  ds.start();//开始测量（所有传感器）
  /////////判断转换是否完成
  ///只有在三根线连接模式下有效,两根线模式下请不要使用
  //  while(!ds.ready()){
  //    delay(10);
  //  }  
  ////////////
  delay(200);//2根线连接模式
  
  float a=ds.get();

  Serial.print("c0=");
  if(a>200){ //CRC 校验错误
    Serial.println("CRC error");
  }
  else{  
    Serial.print(a); 
  }
  
  //下面的不重要
  //   void set(byte n);//set(0x1F) 9位模式 delay(94) ;
                             //0x3F 10位模式 delay(188);
                             //0x5F 11位模式 delay(375);
                             //0x7F 12 位模式 delay(750);
}


