/*  RGBDigitV2 class header .h file

Copyright (C) 2017 Erik Homburg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef RGBDigitV2_h
#define RGBDigitV2_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//https://github.com/adafruit/Adafruit_NeoPixel

/*
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

This software is a fine tuning of the work of Cr�tzen 2015 (Githubg RGBDigit.)
Existing software using the original RGBDigit class will need some modification.
The main reason for class changes is the reduction of the RAM memory footprint
of the class and a streamlining of the class interface.

Mayor changes with respect to the original version:

- The encoding matrices for alphanumeric characters are changed into a more
  packed format: 8 bits are moved into one byte giving 8 fould smaller memory
  footprint. Both matrices are also combined into a single array. The encoding
  of special characters is moved into the class code, yielding some more free
  bytes of RAM. Some characters are redesigned so that they can be distinguished
  without the use of the decimal point. The decimal point is handled separately
  in another method.

- The array containing the color values for the pixel string has been removed.
  The underlying Adafruit_NeoPixel class already has such an array. The Adafruit
  implementation is somewhat lossy: at lower brightness levels the color values
  in the array get changed or even lost due to truncation effects. Hence the
  segmentLit() function cannot reliably use this array to determine wether a pixel
  is lit or not. A byte array (_pixelMap) with only one byte per digit is used
  to maintain a map of lit digits.

- Both setDigit methods with char and int parameters are merged into one method.

- New methods setPattern and setText.

- Pixel colors can be specified with red,green,blue triplets and with the packed
  uint32_t type.   The latter is handy if you want to use color names.

- The setBrightness and getBrightness are removed because they are already present
  in the underlying Adafruit_NeoPixel class.

- showDot, segmentOn and segmentOff have been renamed to setDot, setSegment and
  clearSegment in order to   get a consistent function name scheme.

- isSegmentOn renamed to segmentLit for cosmetical reasons

- After issuing a disableAutoShow() the LED's are not updated until the next show()
  command. enableAutoShow() reenables automatic LED updating, and also calls show()
  for convenience.

- The setColor methods have been renamed to reColor.
*/

class RGBDigit : public Adafruit_NeoPixel {
  public:

    // The constructor of the RGBDigit class.
    // <nDigits> is the number of digits. <pin> is the pin number,
    // which defaults to pin 12 if this parameter is omitted.
    RGBDigit(unsigned int nDigits, int pin = 12);

    // Initialize RGBDigit:
    void begin();

    // Clear all digits:
    void clearAll();

    // Show a character on <digit>.
    // If the ascii value of char is between 0 and 15 a hexadecimal
    // symbol 0..F is shown. This of course include 0..9 in decimal.
    // Otherwise show character on <digit>. Valid characters are letters
    // (case insensitive) from a to z, dash (-), underscore (_),
    // brackets ( ( ) { } [ ] ) and space. A special character (3 bars)
    // is used for ascii values not supported.
    // Use an asterisk (*) for the degree sign:
    void setDigit(char x, unsigned int digit,  byte red, byte green, byte blue );
    void setDigit(char x, unsigned int digit,  uint32_t c);

    // Show dot on <digit>:
    void setDot(unsigned int digit, byte red, byte green, byte blue);
    void setDot(unsigned int digit, uint32_t c);

    // Show segment on <digit>:
    void setSegment(unsigned int digit, byte segment, byte red, byte green, byte blue);
    void setSegment(unsigned int digit, byte segment, uint32_t c);

    // Write a bit pattern to <digit>.
    // The rightmost (lowest) bit controls the A segment and
    // the leftmost (highest) bit controls the decimal point.
    // if a bit in <pattern> equals 1 the corresponding segemnt
    // is set to color rgb(red,green,blue), otherwise to black (0):
    void setPattern(byte pattern, unsigned int digit, byte red, byte green, byte blue);
    void setPattern(byte pattern, unsigned int digit, uint32_t c);

    // Write the text t from <start> up to <start> + <length>  in char t[]
    // or String t to the RGBDigit display:
    void setText(char t[], int start, int length, byte red, byte green, byte blue);
    void setText(char t[], int start, int length, uint32_t c);
    void setText(String t, int start, int length, byte red, byte green, byte blue);
    void setText(String t, int start, int length, uint32_t c);

    // Clear digit, dot, segment:
    void clearDigit(unsigned int digit);
    void clearDot(unsigned int digit);
    void clearSegment(unsigned int digit, byte segment);

    // Returns true if segment on digit is on. Otherwise, returns false:
    bool segmentLit(unsigned int digit, byte segment);


    // Recolor a lit segment, dot possible
    void reColorSegment(unsigned int digit, byte segment, byte red, byte green, byte blue);
    void reColorSegment(unsigned int digit, byte segment, uint32_t c);
    // Recolor displayed digit, exclude dots
    void reColor(unsigned int digit, byte red, byte green, byte blue);
    void reColor(unsigned int digit, uint32_t c);
    // Recolor all displayed digits, exclude dots
    void reColor(byte red, byte green, byte blue);
    void reColor(uint32_t c);

    // Enable automatic pixel update, issue a show() command
    void enableAutoShow();
    // Disable automatic pixel update:
    void disableAutoShow();

  private:

    bool _autoShow;
    byte* _pixelMap;

};

#endif
