/*
  PulseGenFree.h - Library for Pulse Generator Free
  Created by Andy Huang, May,6,2013.
  Tradition Chinese Forum http://bbs.game7777.net
  Tradition Chinese wiki http://www.game7777.net
  Special Thanks: 星空, 看海的日子, 夜, Boku , 小清新, 咖啡冻, darkorigin 
  
  
  特性：
  1. 不停止 cpu 运行, 不使用 delay() delaymicroseconds() 。
  2. 脉冲计数。(Not implement yet, infact you can do it very simple.)
  3. 指定脉冲 on off 时间, us 微秒。
  4. 可同时使用多个引脚进行不同脉冲。
  
  使用方式：
  1. 建构时指定 引脚 on时间 off 时间
  2. 每个循环呼叫 generator()
  3. 暂时不需要脉冲时, 停止呼叫 generator() 即可
  4. 重新需要输出脉冲时，必须先呼叫 init() 一次。时间及计数归零。

  注意事项：
  1. 暂停後重新启动脉冲, 如果未先呼叫 init() , 第一次所产生的脉冲时长最多可能达到71.5分钟。
  
  特性：
  1. 不停止 cpu 運行, 不使用 delay() delaymicroseconds() 。
  2. 脈衝計數。(Not implement yet, infact you can do it very simple.)
  3. 指定脈衝 on off 時間, us 微秒。
  4. 可同時使用多個引腳進行不同脈衝。
  
  使用方式：
  1. 建構時指定 引腳 on時間 off 時間
  2. 每個迴圈呼叫 generator()
  3. 暫時不需要脈衝時, 停止呼叫 generator() 即可
  4. 重新需要輸出脈衝時，必須先呼叫 init() 一次。時間及計數歸零。

  注意事項：
  1. 暫停後重新啟動脈衝, 如果未先呼叫 init() , 第一次所產生的脈衝時長最多可能達到71.5分鐘。

  
*/


#ifndef PulseGenFree_h
#define PulseGenFree_h

#include "Arduino.h"

class PulseGenFree{
public:
	/* 建立 pulse 
	/* @param pin 			第几引脚
	/* @param onInterval	脉冲 ON 的时间 微秒 us
	/* @param offInterval	脉冲 OFF 的时间 微秒 us
	*/
	PulseGenFree(int pin,unsigned int onInterval,unsigned int offInterval);
	
	/* 重新初始化
	/* @param onInterval	脉冲 ON 的时间 微秒 us
	/* @param offInterval	脉冲 OFF 的时间 微秒 us
	*/
	void init(unsigned int onInterval,unsigned int offInterval);
	
	/* 执行
	*/
	void generator();
	

	
private:

	int _pin;							//指定引脚
	unsigned long pulseOnInterval;		//on时间
	unsigned long pulseOffInterval;		//off时间
	
	unsigned long oldTime;				//比对用
	unsigned long newTime;				//比对用
	
	bool pulseState;					//脉冲状态

};

#endif