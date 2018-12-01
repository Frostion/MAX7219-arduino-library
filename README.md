# Arduino MAX7219 7-segment display library

This is a simple library for displaying numbers on a 7-segment display that is being driven with a MAX7219 IC.

## Example program

This program displays the number of seconds that the Arduino has been running on a 7-segment display with 8 digits.
```
#include <MAX7219.h> //include library

//digital pins used for interfacing with the display
#define MAX_DATA 13
#define MAX_LATCH 12
#define MAX_CLOCK 11

//the number of digits the display has, up to 8
#define NUM_DIGITS 8

//MAX7219 display object
MAX7219 disp(MAX_DATA,MAX_CLOCK,MAX_LATCH,NUM_DIGITS);

void setup()
{
  //set up the display
  disp.init();
}

void loop()
{
  //get the number of seconds that the program has been running for
  float seconds = millis() / 1000.0;

  //show the number on the display, with 2 decimal places
  disp.writeFloat(seconds,MAX_CHAR_BLANK,2);
  disp.updateDisplay();
  delay(10);
}
```
## Using the library

### Declaring the MAX7219 object

`MAX7219 object_name(data_pin,clock_pin,latch_pin,num_digits);	`

 - `object_name` is the name of the object
 - `data_pin` is the Arduino pin that the MAX7219 data/DIN pin is connected to
 - `clock_pin` is the Arduino pin that the MAX7219 clock pin is connected to
 - `latch_pin` is the Arduino pin that the MAX7219 latch/CS pin is connected to
 - `num_digits` is the number of digits on the display (1 to 8)

### Functions available

`void MAX7219::init()` - Sets up the display. Must be called before the display is used for it to work correctly.

`void MAX7219::writeRegister(uint8_t address,uint8_t data)` - Writes a byte directly to one of the control registers of the MAX7219.

`void MAX7219::setBrightness(uint8_t brightness)` - Sets the brightness of the entire display (0 is lowest, 15 is highest).

`void MAX7219::setDecodeMode(uint8_t mode)` - Sets if the MAX7219 should display the digit values as numbers, or use them to directly light up individual segments on the display. By default, the library sets all digits to display the values as numbers. Use `MAX_MODE_BCD` to to display the values as numbers, or `MAX_MODE_RAW` to display the values as individual segments. See the "BCD and RAW decode modes" section below for more info.

`void MAX7219::updateDisplay()` - Sends the contents of VRAM to the display.

`void MAX7219::fillDisplay(uint8_t data)` - Sets all of the digits of the display to a specific value.

`void MAX7219::writeDigit(uint8_t digit,uint8_t data)` - Sets the contents of a single digit.

`void MAX7219::setDecimalPoint(uint8_t digit)` - Turns on the decimal point of a specific digit.

`uint8_t MAX7219::readDigit(uint8_t digit)` - Returns the contents of a specific digit.

`void MAX7219::writeLong(unsigned long num,uint8_t padding_char)` - Writes an integer, long, or other non-float number to the display. If the number has less than 8 digits, the unused digits to the left of the number are filled with `padding_char`. Also automatically sets the display to BCD mode.

`void MAX7219::writeFloat(float num,uint8_t padding_char,uint8_t decimal_places)` - Writes a float to the display. If the number has less than 8 digits, the unused digits to the left of the number are filled with `padding_char`. `decimal_places` is the number of digits to display to the right of the decimal point. Also automatically sets the display to BCD mode.

### Constants available

`MAX_REG_DIGIT` - The address of the place in the MAX7219's memory to start writing digit display data to.

`MAX_REG_DECODE` - The address of the decode mode byte in the MAX7219's memory.

`MAX_REG_BRIGHTNESS` - The address of the brightness value byte in the MAX7219's memory.

`MAX_REG_SCANLIMIT` - The address of the number of digits - 1 in the MAX7219's memory.

`MAX_REG_ENABLED` - The address of the shutdown bit in the MAX7219's memory. The display is completely blanked when this is set to 0.

`MAX_REG_LAMPTEST` - The address of the display test bit in the MAX7219's memory. Every segment of the display is turned on when this is set to 1.

`MAX_MODE_BCD` - Use with the `setDecodeMode` function to set the display to BCD mode (it will interpret all digit values as numbers to display). See the "BCD and RAW decode modes" section below for more info.

`MAX_MODE_RAW` - Use with the `setDecodeMode` function to set the display to raw mode (it will interpret all digit values as 'bitmaps').

`MAX_CHAR_ZERO` - When in BCD mode, this character will display a 0.

`MAX_CHAR_DASH` - When in BCD mode, this character will display a dash (-).

`MAX_CHAR_BLANK` - When in BCD mode, this character will turn off that digit and not show anything.

`MAX_CHAR_DECIMALPOINT` - In any mode, this character will turn on only the digit's decimal point.

### BCD and RAW decode modes

When in BCD mode (achieved by calling `setDecodeMode(MAX_MODE_BCD)`), the bytes written to the digits are interpreted by the display as numbers. So, a 0 will display a 0, 1 will display a 1, and so on. There are a few other special characters that can be used in BCD mode as well.
|Character|Value|
|--|--|
|0|`0x0`|
|1|`0x1`|
|2|`0x2`|
|3|`0x3`|
|4|`0x4`|
|5|`0x5`|
|6|`0x6`|
|7|`0x7`|
|8|`0x8`|
|9|`0x9`|
|-|`0xA`|
|E|`0xB`|
|H|`0xC`|
|L|`0xD`|
|P|`0xE`|
|*blank*|`0xF`|

When in RAW mode (achieved by calling `setDecodeMode(MAX_MODE_RAW)`), the individual segments of each digit can be controlled directly. Each bit in the byte written to the digit controls one of the digit's 8 segments:
![Chart of segments](https://i.imgur.com/IkFAebV.png)
