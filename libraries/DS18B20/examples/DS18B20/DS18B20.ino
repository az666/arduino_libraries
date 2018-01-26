#include "DS18B20.h"
//DS18B20(byte pin,byte sn)  连接管脚，传感器数量
//传感器设定为10位模式，每次转换时间<187.5ms,如果需要12位模式，请修改库文件of ds.set(0x7F);
DS18B20  ds(9,2);//pin9，连接2个DS18B20

void setup() {
  Serial.begin(9600);

  ///////////不重要，可以省略
  byte i;
  byte j;
  for (j = 0; j < ds.getNumber(); j++) {
    for (i = 0; i < 8; i++) {
      Serial.print(ds.senser_addr[j][i]);
      Serial.print(",");
    }
    Serial.print("CRC=");
    Serial.print(ds.crc8(ds.senser_addr[j], 7) );
    Serial.println();
  }
  Serial.println(ds.getNumber());
  ////////////////
}

void loop() { 
  ds.start();//开始测量（所有传感器）
  //ds.start(0);// 开始测量（单个）

  /////////判断转换是否完成
  ///只有在三根线连接模式下有效,两根线模式下请不要使用
  //  while(!ds.ready()){
  //    delay(10);
  //  }  
  ////////////
  delay(200);//2根线连接模式
  
  float a=ds.get(0);
  float b=ds.get(1);

  Serial.print("c0=");
  if(a>200){ //CRC 校验错误
    Serial.println("CRC error");
  }
  else{  
    Serial.print(a); 
  }
  
  Serial.print("  c1=");
   if(b>200){//CRC 校验错误
    Serial.println("CRC error"); 
  }
  else{  
    Serial.println(b); //s
  }

  //下面的不重要
  //   void set(byte n);//set(0x1F) 9位模式 delay(94) ;
                             //0x3F 10位模式 delay(188);
                             //0x5F 11位模式 delay(375);
                             //0x7F 12 位模式 delay(750);
  //	byte getNumber();//获取传感器数量
  //	void search_again();//重新搜索 地址 	
  //	byte senser_addr[8][8];//地址储存，最多8个  

}


