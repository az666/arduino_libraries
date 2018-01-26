#ifndef DS18B20_h
#define DS18B20_h

#include <inttypes.h>

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

// You can exclude certain features from DS18B20.  In theory, this
// might save some space.  In practice, the compiler automatically
// removes unused code (technically, the linker, using -fdata-sections
// and -ffunction-sections when compiling, and Wl,--gc-sections
// when linking), so most of these will not result in any code size
// reduction.  Well, unless you try to use the missing features
// and redesign your program to not need them!  DS18B20_CRC8_TABLE
// is the exception, because it selects a fast but large algorithm
// or a small but slow algorithm.



// You can exclude CRC checks altogether by defining this to 0
#ifndef DS18B20_CRC
#define DS18B20_CRC 1
#endif

// Select the table-lookup method of computing the 8-bit CRC
// by setting this to 1.  The lookup table enlarges code size by
// about 250 bytes.  It does NOT consume RAM (but did in very
// old versions of DS18B20).  If you disable this, a slower
// but very compact algorithm is used.
#ifndef DS18B20_CRC8_TABLE
#define DS18B20_CRC8_TABLE 1
#endif


#define FALSE 0
#define TRUE  1



class DS18B20
{
  private:
  	uint8_t PIN;
    byte bitmask;

    // global search state
    byte ROM_NO[8];//search到的最新地址暂存
    
    uint8_t LastDiscrepancy;
    uint8_t LastDeviceFlag;
    byte search_new();
    byte senser_number; 
    
    void write(uint8_t v);    
    void write_bytes(const uint8_t *buf, uint16_t count);
    // Read a byte.
    uint8_t read(void);
    void read_bytes(uint8_t *buf, uint16_t count);
    // Write a bit. The bus is always left powered at the end, see
    // note in write() about that.
    void write_bit(uint8_t v);
    // Read a bit.
    uint8_t read_bit(void);
    // Issue a 1-Wire rom select command, you do the reset first.
    void select(const uint8_t rom[8]);
    // Perform a 1-Wire reset cycle. Returns 1 if a device responds
    // with a presence pulse.  Returns 0 if there is no device or the
    // bus is shorted or otherwise held low for more than 250uS
    uint8_t reset(void);
    // Clear the search state so that if will start from the beginning again.
    void reset_search();
    void search();    
  public:
  	void set(byte n);
  	byte getNumber();
  	void search_again();//重新搜索  	
  	byte senser_addr[8][8];//地址储存，最多8个  	
    DS18B20( uint8_t pin,byte sn);
    float get(byte n);
    void start(byte n);
    void start();
    boolean ready();
    // Look for the next device. Returns 1 if a new address has been
    // returned. A zero might mean that the bus is shorted, there are
    // no devices, or you have already retrieved all of them.  It
    // might be a good idea to check the CRC to make sure you didn't
    // get garbage.  The order is deterministic. You will always get
    // the same devices in the same order.
    

#if DS18B20_CRC
    // Compute a Dallas Semiconductor 8 bit CRC, these are used in the
    // ROM and scratchpad registers.
    static uint8_t crc8(const uint8_t *addr, uint8_t len);

#endif
};

#endif