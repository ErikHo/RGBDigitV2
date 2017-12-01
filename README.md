# RGBDigitV2
Arduino library for RGBDigits http://www.rgbdigit.com/

This library is a replacement for the original RGBDigit library ( Crützen 2015 ).
The memory footprint is reduced significantly and colors can also specified with
a single 32bit word as defined in the underlying Adafruit_NeoPixel Class.

This software is a fine tuning of the work of Crützen 2015 (Github RGBDigit).
Existing software using the original RGBDigit class will need modification.
The main reason for class changes is the reduction of the RAM memory footprint
of the class and a streamlining of the class interface.


## Installation instructions
* Download the zip file
* Extract it to your Arduino library folder
* If needed rename the RGBDigit3-master folder to RGBDigit3

You also have to download and install the following library:
* Adafruit NeoPixel https://github.com/adafruit/Adafruit_NeoPixel

See the demonstration sketches in the examples directory.

The RGBdigit class is an interface to RGBDigits (www.rgbdigit.com), a 7 segment
display based on NeoPixel leds (Adafruit NeoPixel). Multiple RGBDigits can form
a display line. Each RGBdigit contains a string of 8 NeoPixels arranged in the
classical 7 segment configuration. The segments are adressed with a segment
parameter 0..7 indicating the segments A..G and the decimal point P:

         AAA         AAA         AAA         AAA
       F     B     F     B     F     B     F     B
       F     B     F     B     F     B     F     B
         GGG         GGG         GGG         GGG
       E     C     E     C     E     C     E     C
       E     C     E     C     E     C     E     C
         DDD   P     DDD   P     DDD   P     DDD   P

       digit 0     digit 1     digit 2     digit 3

Multiple RGBDigits are adressed with a parameter digit that is zero-based:
the first RGBDigit is 0, second is 1, etc.
Pixel colors can be specified with red,green,blue triplets and with the packed
uint32_t type as defined in the underlying Adafruit_Neopixel class.


## Class methods
Constructor of the RGBDigit class. <nDigits> is the number of digits.  
<pin> is the pin number, which defaults to pin 12 if this parameter is omitted:  
**RGBDigit(int nDigits, int pin = 12);**  

Initialize RGBDigit:    
**void begin();**

Clear all digits:  
**void clearAll();**

Show a character on <digit>.
If the ascii value of char is between 0 and 15 a hexadecimal symbol 0..F
is shown. This of course includes 0..9 in decimal. Otherwise show character
on <digit>. Valid characters are letters (case insensitive) from a to z,
dash -, underscore _, brackets  \(, \), \{, \}, \[, \] and space. A special
character (3 bars) is used for ascii values not supported. Use an asterisk(*)
for the degree sign:  
**void setDigit(char x, unsigned int digit,  byte red, byte green, byte blue );**  
**void setDigit(char x, unsigned int digit,  uint32_t c);**

Show dot on <digit>:  
**void setDot(unsigned int digit, byte red, byte green, byte blue);**  
**void setDot(unsigned int digit, uint32_t c);**

Show segment on <digit>:  
**void setSegment(unsigned int digit, byte segment, byte red, byte green, byte blue);**  
**void setSegment(unsigned int digit, byte segment, uint32_t c);**  

Write a bit pattern to <digit>.  
The rightmost (lowest) bit controls the A segment and
the leftmost (highest) bit controls the decimal point.
if a bit in <pattern> equals 1 the corresponding segemnt
is set to color rgb(red,green,blue), otherwise to black (0):  
**void setPattern(byte pattern, unsigned int digit, byte red, byte green, byte blue);**  
**void setPattern(byte pattern, unsigned int digit, uint32_t c);**  

Write the text t from <start> up to <start> + <length>  in char t[]
or String t to the RGBDigit display:  
**void setText(char t[], int start, int length, byte red, byte green, byte blue);**  
**void setText(char t[], int start, int length, uint32_t c);**  

Clear digit, dot, segment:  
**void clearDigit(unsigned int digit);**  
**void clearDot(unsigned int digit);**  
**void clearSegment(unsigned int digit, byte segment);**  

Returns *true* if segment on digit is on. Otherwise, returns *false*:  
**bool segmentLit(unsigned int digit, byte segment);**  

Recolor a lit segment, dot possible:  
**void reColorSegment(unsigned int digit, byte segment, byte red, byte green, byte blue);**  
**void reColorSegment(unsigned int digit, byte segment, uint32_t c);**  
Recolor a displayed digit, exclude dots:  
**void reColor(unsigned int digit, byte red, byte green, byte blue);**  
**void reColor(unsigned int digit, uint32_t c);**  
Recolor all displayed digits, exclude dots:  
**void reColor(byte red, byte green, byte blue);**  
**void reColor(uint32_t c);**  

Enable automatic pixel update, issue a show() command:  
**void setAutoShow();**  
Disable automatic pixel update:  
**void clearAutoShow();**  

