#ifndef MAX7219_h
#define MAX7219_h

//library for using MAX7129 to drive 7-segment numerical displays
//created by Frost Sheridan - Dec 2018

#include "Arduino.h"

#define MAX_REG_DIGIT 0x01
#define MAX_REG_DECODE 0x09
#define MAX_REG_BRIGHTNESS 0x0A
#define MAX_REG_SCANLIMIT 0x0B
#define MAX_REG_ENABLED 0x0C
#define MAX_REG_LAMPTEST 0x0F
#define MAX_CHAR_DASH 0b00000001
#define MAX_CHAR_UNDERSCORE 0b00001000
#define MAX_CHAR_BLANK 0
#define MAX_CHAR_DECIMALPOINT 128

const uint8_t MAX_NUMBERS[16] = {0b01111110,0b00110000,0b01101101,0b01111001,0b00110011,0b01011011,0b01011111,0b01110000,0b01111111,0b01111011,0b01110111,0b00011111,0b01001110,0b00111101,0b01001111,0b01000111};

class MAX7219
{
	public:
		MAX7219(uint8_t pin_data,uint8_t pin_clock,uint8_t pin_latch,uint8_t num_digits);
		void init();
		void writeRegister(uint8_t address,uint8_t value);
		void setBrightness(uint8_t brightness);
		void updateDisplay();
		void fillDisplay(uint8_t data);
		void writeDigitRaw(uint8_t digit,uint8_t data);
		void writeDigitNumber(uint8_t digit,uint8_t num);
		void setDecimalPoint(uint8_t digit);
		uint8_t readDigit(uint8_t digit);
		void writeLong(unsigned long num,uint8_t padding_char);
		void writeFloat(float num,uint8_t padding_char,uint8_t decimal_places);
		
		uint8_t vram[8] = {0,0,0,0,0,0,0,0};
	private:
		uint8_t _pin_data, _pin_clock, _pin_latch, _num_digits;
};

#endif