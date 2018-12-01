//library for using MAX7129 to drive 7-segment numerical displays
//created by Frost Sheridan - Dec 2018

#include "Arduino.h"
#include "MAX7219.h"

MAX7219::MAX7219(uint8_t pin_data,uint8_t pin_clock,uint8_t pin_latch,uint8_t num_digits)
{
	pinMode(pin_data,OUTPUT);
	pinMode(pin_clock,OUTPUT);
	pinMode(pin_latch,OUTPUT);
	
	_pin_data = pin_data;
	_pin_clock = pin_clock;
	_pin_latch = pin_latch;
	_num_digits = num_digits;
}

void MAX7219::init()
{
	writeRegister(MAX_REG_LAMPTEST,0);
	writeRegister(MAX_REG_BRIGHTNESS,0x8);
	writeRegister(MAX_REG_ENABLED,0);
	writeRegister(MAX_REG_SCANLIMIT,_num_digits - 1);
	writeRegister(MAX_REG_DECODE,MAX_MODE_BCD);
}

void MAX7219::writeRegister(uint8_t address,uint8_t data)
{
	digitalWrite(_pin_latch,0);
	shiftOut(_pin_data,_pin_clock,MSBFIRST,address);
	shiftOut(_pin_data,_pin_clock,MSBFIRST,data);
	digitalWrite(_pin_latch,1);
}

void MAX7219::setBrightness(uint8_t brightness)
{
	writeRegister(MAX_REG_BRIGHTNESS,brightness & 0xF);
}

void MAX7219::setDecodeMode(uint8_t mode)
{
	writeRegister(MAX_REG_DECODE,mode);
}

void MAX7219::updateDisplay()
{
	writeRegister(MAX_REG_ENABLED,0);
	for(uint8_t digit = 0; digit < _num_digits; digit++)
	{
		writeRegister(MAX_REG_DIGIT + digit,vram[digit]);
	}
	writeRegister(MAX_REG_ENABLED,1);
}

void MAX7219::fillDisplay(uint8_t data)
{
	for(uint8_t digit = 0; digit < _num_digits; digit++)
	{
		vram[digit] = data;
	}
}

void MAX7219::writeDigit(uint8_t digit,uint8_t data)
{
	vram[digit] = data;
}

void MAX7219::setDecimalPoint(uint8_t digit)
{
	vram[digit] |= MAX_CHAR_DECIMALPOINT;
}

uint8_t MAX7219::readDigit(uint8_t digit)
{
	return vram[digit];
}

void MAX7219::writeLong(unsigned long num,uint8_t padding_char)
{
	setDecodeMode(MAX_MODE_BCD);
	
	for(uint8_t digit = 0; digit < _num_digits; digit++)
	{
		if(num == 0)
		{
			writeDigit(digit,padding_char);
		}
		else
		{
			writeDigit(digit,num % 10);
			num /= 10;
		}
	}
}

void MAX7219::writeFloat(float num,uint8_t padding_char,uint8_t decimal_places)
{
	setDecodeMode(MAX_MODE_BCD);
	
	unsigned long num_int_part = num;
	float num_float_part = num - num_int_part;
	
	for(int8_t digit = decimal_places - 1; digit >= 0; digit--)
	{
		num_float_part *= 10;
		writeDigit(digit,long(num_float_part) % 10);
	}
	
	for(uint8_t digit = decimal_places; digit < _num_digits; digit++)
	{
		if(num_int_part == 0)
		{
			writeDigit(digit,padding_char);
		}
		else
		{
			writeDigit(digit,num_int_part % 10);
			num_int_part /= 10;
		}
	}
	
	setDecimalPoint(decimal_places);
}