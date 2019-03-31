# Arduino MAX7219 7-segment display library by Frost Sheridan

This is a simple library for displaying numbers on a 7-segment display that is being driven with a MAX7219 IC.

## Using the library

### Declaring the MAX7219 object

`MAX7219 object_name(data_pin,clock_pin,latch_pin,num_digits);`

 - `object_name` is the name of the object
 - `data_pin` is the Arduino pin that the MAX7219 data/DIN pin is connected to
 - `clock_pin` is the Arduino pin that the MAX7219 clock pin is connected to
 - `latch_pin` is the Arduino pin that the MAX7219 latch/CS pin is connected to
 - `num_digits` is the number of digits on the display (1 to 8)

### Functions available

`void MAX7219::init()` - Sets up the display. Must be called before the display is used for it to work correctly.

`void MAX7219::writeRegister(uint8_t address,uint8_t data)` - Writes a byte directly to one of the control registers of the MAX7219.

`void MAX7219::setBrightness(uint8_t brightness)` - Sets the brightness of the entire display (0 is lowest, 15 is highest).

`void MAX7219::updateDisplay()` - Sends the contents of VRAM to the display. Must be called to make any changes made to the contents of the display visible.

`void MAX7219::fillDisplay(uint8_t data)` - Sets all of the digits of the display to a specific value. *(Hint: to clear the display, use `fillDisplay(MAX_CHAR_BLANK)`)*

`void MAX7219::writeDigitRaw(uint8_t digit,uint8_t data)` - Sets the contents of a single digit as a raw 'bitmap' of the segments.

`void MAX7219::writeDigitNumber(uint8_t digit,uint8_t num)` - Displays a single decimal/hexadecimal digit (`num` can be between 0-15).

`void MAX7219::setDecimalPoint(uint8_t digit)` - Turns on the decimal point of a specific digit.

`uint8_t MAX7219::readDigit(uint8_t digit)` - Returns the contents of a specific digit as a raw 'bitmap' of the segments.

`void MAX7219::writeLong(unsigned long num,uint8_t padding_char)` - Writes an integer, long, or other non-float number to the display. If the number has less than 8 digits, the unused digits to the left of the number are filled with `padding_char`.

`void MAX7219::writeFloat(float num,uint8_t padding_char,uint8_t decimal_places)` - Writes a float to the display. If the number has less than 8 digits, the unused digits to the left of the number are filled with `padding_char`. `decimal_places` is the number of digits to display to the right of the decimal point.

### Constants available

##### Characters (use with `writeDigitRaw` function)

`MAX_CHAR_DASH` - Shows a dash `-` character

`MAX_CHAR_UNDERSCORE` - Shows an underscore `_` character

`MAX_CHAR_BLANK` - Blanks the digit it's written to

`MAX_CHAR_DECIMALPOINT` - Turns on only the decimal point of the digit it's written to

`MAX_NUMBERS[]` - An array containing the 16 hexadecimal digit characters that the `writeDigitNumber` function uses

##### Internal registers (use with `writeRegister   ` function)

`MAX_REG_DIGIT` - The address of the place in the MAX7219's memory to start writing digit display data to.

`MAX_REG_DECODE` - The address of the decode mode byte in the MAX7219's memory.

`MAX_REG_BRIGHTNESS` - The address of the brightness value byte in the MAX7219's memory.

`MAX_REG_SCANLIMIT` - The address of the number of digits - 1 in the MAX7219's memory.

`MAX_REG_ENABLED` - The address of the shutdown bit in the MAX7219's memory. The display is completely blanked when this is set to 0.

`MAX_REG_LAMPTEST` - The address of the display test bit in the MAX7219's memory. Every segment of the display is turned on when this is set to 1.

### How the segments map to bits
When using the `writeDigitRaw` function, you write a byte to the display to turn on/off the individual segments of a digit. Each bit in that byte controls one of the digit's 8 segments:
![Chart of segments](https://i.imgur.com/IkFAebV.png)
