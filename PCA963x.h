#include <Arduino.h>

const PROGMEM byte MODE1 = 0x00;
const PROGMEM byte MODE2 = 0x01;

//Mode 1 options
const PROGMEM byte ALLCALL 	= 0b00000001; // PCA9633 responds to LED All Call I2C-bus address.
const PROGMEM byte SUB3 		= 0b00000010; // PCA9633 responds to I2C-bus subaddress 3.
const PROGMEM byte SUB2 		= 0b00000100; // PCA9633 responds to I2C-bus subaddress 2.
const PROGMEM byte SUB1 		= 0b00001000; // PCA9633 responds to I2C-bus subaddress 1.
const PROGMEM byte SLEEP 	= 0b00010000; // Low power mode. Oscillator off
const PROGMEM byte AI0 		= 0b00100000; // Auto-Increment bit0=1
const PROGMEM byte AI1 		= 0b01000000; // Auto-Increment bit1=1
const PROGMEM byte AI2 		= 0b10000000; // Register Auto-Increment enabled

//Mode 2 options
//const PROGMEM byte OUTNE0 	= 0b00000000; // When OE = 1 (output drivers not enabled), LEDn = 0.
const PROGMEM byte OUTNE0 	= 0b00000001; // When OE = 1 (output drivers not enabled): LEDn = 1 when OUTDRV = 1 LEDn = high-impedance when OUTDRV = 0 (same as OUTNE[1:0] = 10)
const PROGMEM byte OUTNE1 	= 0b00000010; // When OE = 1 (output drivers not enabled), LEDn = high-impedance.

const PROGMEM byte OUTDRV 	= 0b00000100; // 0 The 4 LED outputs are configured with an open-drain structure., 1* The 4 LED outputs are configured with a totem pole structure.
const PROGMEM byte OCH	 	= 0b00001000; // 1 Outputs change on ACK., 0 Outputs change on STOP command.
const PROGMEM byte INVRT 	= 0b00010000; // Output logic state not inverted. Value to use when no external driver used. Applicable when OE = 0 for PCA9633 16-pin version. 1 Output logic state inverted. Value to use when external driver used.Applicable when OE = 0 for PCA9633 16-pin version.
const PROGMEM byte DMBLNK 	= 0b00100000; // 1 Group control = blinking, 0 Group control = dimming

//default modes
const PROGMEM byte MODE1_DEFAULT = B10010001;
const PROGMEM byte MODE2_DEFAULT = B00000101;

//PCA963x models
const PROGMEM byte PCA9633 = 0;
const PROGMEM byte PCA9634 = 4; //led offset
const PROGMEM byte PCA9635 = 12;//led offset

const PROGMEM byte LEDOUT0 = 0x08;
/*
const int LEDOUT0 = 0x14;
const int LEDOUT1 = 0x15;
const int LEDOUT2 = 0x16;
const int LEDOUT3 = 0x17;
*/

class PCA963x
{
public:
	PCA963x(byte address);
	PCA963x(byte address, byte chipType);
	int begin();
	int reset();
	byte getMode1();
	byte getMode2();
	void setMode1(byte value);
	void setMode2(byte value);
	void analogWrite(int pin, byte value);
	void digitalWrite(int pin, int value);
	
	private:
	  int _address;
	  int _ledout_offset;
	// interface to I2C
	void setRegister(int reg, byte value);
	int getRegister(int reg);
};

