#include <PCA963x.h>
#include <Wire.h>

PCA963x::PCA963x(byte address)
{
  _address = address;
  _ledout_offset = PCA9633; 
}

PCA963x::PCA963x(byte address, byte chipType)
{
  _address = address;
  _ledout_offset = chipType; 
}

int PCA963x::begin()
{
	Wire.beginTransmission(_address);
  	int result = Wire.endTransmission();
  
	if (result==0)
	{
		setRegister(MODE1, MODE1_DEFAULT);
		setRegister(MODE2, MODE2_DEFAULT);
		
		setRegister(LEDOUT0+_ledout_offset, 0xFF);
		if (_ledout_offset >=4)
			setRegister(LEDOUT0+_ledout_offset+1, 0xFF);
		if (_ledout_offset >=12) {
			setRegister(LEDOUT0+_ledout_offset+2, 0xFF); 
			setRegister(LEDOUT0+_ledout_offset+3, 0xFF);
		}
	}
	return result;
}

int PCA963x::reset(){
	Wire.beginTransmission(0b00000110);
	Wire.write(0xA5);
	Wire.write(0x5A);
  	int result = Wire.endTransmission();
	return result;
}

byte PCA963x::getMode1(){
	int x = getRegister(MODE1);
	return x;
}

byte PCA963x::getMode2(){
	int x = getRegister(MODE2);
	return x;
}

void PCA963x::setMode1(byte value){
	setRegister(MODE1,value);
	delayMicroseconds(500);
}

void PCA963x::setMode2(byte value){
	setRegister(MODE2,value);
	//delayMicroseconds(500);
}

void PCA963x::digitalWrite(int pin, int value)
{
	//which LEDOUT are we talking about?
	int ledout = pin/4;
	
	if (value == HIGH)
	{
		int x = getRegister(LEDOUT0+_ledout_offset+ledout);
		x &= ~(0x03 << 2*(pin%4));
		x |=  (0x01 << 2*(pin%4));
		setRegister(LEDOUT0+_ledout_offset+ledout, x);
	}
	else if (value == LOW)
	{
		int x = getRegister(LEDOUT0+_ledout_offset+ledout);
		x &= ~(0x03 << 2*(pin%4));
		setRegister(LEDOUT0+_ledout_offset+ledout, x);
	}
	else
	{
		// throw exception?
	}
}


void PCA963x::analogWrite(int pin, byte value)
{
	int reg = 0x2 + pin;

	setRegister(reg, value);
}


int PCA963x::getRegister(int reg)
{
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_address, 1);
	while(Wire.available()<1) // necessary?
	{
		;
	}
	int retval = Wire.read();
	return retval;
}

void PCA963x::setRegister(int reg, byte value)
{
  //WRITE LED0 byte
  Wire.beginTransmission(_address);

  Wire.write(reg);
  Wire.write(value);

  int result = Wire.endTransmission();

  //return result;
}


