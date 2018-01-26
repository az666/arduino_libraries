/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library 
* @brief        Datapoints handle , Gizwits Process
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A2, A3); // A2 -> RX, A3 -> TX

Gizwits myGizwits;

/**
* Serial Init , Gizwits Init  
* @param none
* @return none
*/
void setup() {
  // put your setup code here, to run once:

  mySerial.begin(115200);

  myGizwits.begin();

  mySerial.println("GoKit init  OK \n");

}

/**
* Arduino loop 
* @param none
* @return none
*/
void loop() {  
  
  //Configure network
  //if(XXX) //Trigger Condition
  //myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
    /*
  unsigned long varW_T_test = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_T_test, varW_T_test);
  unsigned long varW_H_test = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_H_test, varW_H_test);


  bool varR_on_off = 0;
  if(myGizwits.hasBeenSet(EVENT_on_off))
  {
    myGizwits.read(EVENT_on_off,&varR_on_off);//Address for storing data
    mySerial.println(F("EVENT_on_off"));
    mySerial.println(varR_on_off,DEC);

  }
  unsigned long varR_message_test = 0;
  if(myGizwits.hasBeenSet(EVENT_message_test))
  {
    myGizwits.read(EVENT_message_test,&varR_message_test);//Address for storing data
    mySerial.println(F("EVENT_message_test"));
    mySerial.println(varR_message_test,DEC);

  }


  //binary datapoint handle
  */

  myGizwits.process();
}