/*  RGBDigitV2 class body .cpp file
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

#include "RGBDigitV2.h"

RGBDigit::RGBDigit(unsigned int nDigits, int pin)
  : Adafruit_NeoPixel(8 * nDigits, pin, NEO_GRB + NEO_KHZ800){
  _pixelMap = new byte[nDigits];  // Map to store segment status
}

void RGBDigit::begin(){
  Adafruit_NeoPixel::begin();
  enableAutoShow();
}

void RGBDigit::clearAll(){
  // clear from Adafruit_NeoPixel class
  clear();
  // switch all pixels off
  show();
  // retrieve number of digits
  unsigned int nDigits = numPixels() >> 3;
  // clear pixel map
  for(unsigned int digit = 0; digit < nDigits; digit++){
    _pixelMap[digit] = 0;
  }
}

void RGBDigit::setDigit(char x, unsigned int digit, byte red, byte green, byte blue ){
  setDigit( x, digit, Color(red, green, blue));
}

void RGBDigit::setDigit(char x, unsigned int digit, uint32_t c){
  static const byte alphaNum[37] PROGMEM = {
  // .GFEDCBA
    B00111111,     //0     The rightmost bit controls the A segment and the
    B00000110,     //1     leftmost bit controls the decimal point.
    B01011011,     //2     The decimal point bit is however not written.
    B01001111,     //3
    B01100110,     //4
    B01101101,     //5
    B01111101,     //6
    B00000111,     //7
    B01111111,     //8
    B01101111,     //9
    B01110111,     //a
    B01111100,     //b
    B00111001,     //c
    B01011110,     //d
    B01111001,     //e
    B01110001,     //f
    B01101111,     //g
    B01110100,     //h
    B00000110,     //i
    B00001110,     //j
    B01110000,     //k
    B00111000,     //l
    B01010101,     //m
    B01010100,     //n
    B01011100,     //o
    B01110011,     //p
    B01100111,     //q
    B01010000,     //r
    B01101101,     //s
    B01111000,     //t
    B00111110,     //u
    B00011100,     //v
    B01101010,     //w
    B01100100,     //x
    B01101110,     //y
    B01011011      //z
  };

  x = tolower(x);                     // convert to lower case
  byte pattern;
  if((x >= 'a') && (x <='z')){        // get bit pattern for a letter
    pattern = pgm_read_byte_near(alphaNum + x-int('a') + 10);
  }
  else if((x >= '0') && (x <='9')){   // get bit pattern for a digit
    pattern = pgm_read_byte_near(alphaNum + x-int('0'));
  }
  else if((x >= 0) && (x <=0x0F)){    // direct selection of pattern for
    pattern = pgm_read_byte_near(alphaNum + x);      // a (hex) number
  }
  else{                               // special characters
    switch(x){
    case ' ':
      pattern = B00000000;  //space,' '
    break;
    case '-':
      pattern = B01000000;  //minus,'-'
    break;
    case '_':
      pattern = B00001000;  //underscore,'_'
    break;
    case '{':
    case '[':
    case '(':
      pattern = B00111001;  //leftbracket, '('
    break;
    case '}':
    case ']':
    case ')':
      pattern = B00001111;   //rightbracket,')'
    break;
    case '*':
      pattern = B01100011;   //asterisk,'*', used as degree symbol
    break;
    default:
      pattern = B01001001;   //undefined character = 3 horizontal bars
    break;
    }
  }
  setPattern(pattern, digit, c);
}

void RGBDigit::clearDigit(unsigned int digit){
  setDigit(digit,' ',0);
}

// a dot is segment #7
void RGBDigit::setDot(unsigned int digit, byte red, byte green, byte blue){
  setSegment(digit, 7, red, green, blue);
}

void RGBDigit::setDot(unsigned int digit, uint32_t c){
  setSegment(digit, 7, c);
}

void RGBDigit::clearDot(unsigned int digit){
  clearSegment(digit, 7);
}

void RGBDigit::setSegment(unsigned int digit, byte segment, byte red, byte green, byte blue){
  setSegment(digit, segment, Color(red, green, blue));
}

void RGBDigit::setSegment(unsigned int digit, byte segment, uint32_t c){
  setPixelColor((digit << 3) + segment, c);
  if(c > 0){
    // color present: set a pixel bit in the map
    _pixelMap[digit] = _pixelMap[digit] | (1 << segment);
  }
  else{
    // no color present: clear a pixel bit in the map
    _pixelMap[digit] = _pixelMap[digit] & ~(1 << segment);
  };
  if(_autoShow){
    show();
  }
}

void RGBDigit::clearSegment(unsigned int digit, byte segment){
  setSegment(digit, segment, 0);
}

bool RGBDigit::segmentLit(unsigned int digit, byte segment){
  // test pixel map bit
  return (_pixelMap[digit] & (1 << segment)) > 0;
}

void RGBDigit::setPattern(byte pattern, unsigned int digit, uint32_t c){
byte bitMask = 1;
  for (int segment = 0; segment < 7; segment++){
    if (pattern & bitMask)
      setPixelColor((digit <<3)+segment, c);
    else
      setPixelColor((digit <<3)+segment, 0);
    bitMask <<= 1;
  };
  if(c == 0){
    // no color : leave the decimal point and kill all other bits
    _pixelMap[digit] = _pixelMap[digit] & B10000000;
  }
  else{
    // color : leave the decimal point and kill all other bits,
    // add the selected bit pattern
    _pixelMap[digit] = (_pixelMap[digit] & B10000000) | byte(pattern);
  };
  if(_autoShow){
    show();
  }
}

void RGBDigit::setPattern(byte pattern, unsigned int digit, byte red, byte green, byte blue){
  setPattern(pattern, digit, Color(red, green, blue));
}

void RGBDigit::setText(char t[], int start, int length, uint32_t c){
  for(int i =0; i < length; i++){
      setDigit(t[start + i], i, c);
  }
}

void RGBDigit::setText(char t[], int start, int length, byte red, byte green, byte blue){
  setText(t, start, length, Color(red, green, blue));
}

void RGBDigit::setText(String t, int start, int length, byte red, byte green, byte blue){
  setText(t, start, length, Color(red, green, blue));
}

void RGBDigit::setText(String t, int start, int length, uint32_t c){
  for(int i =0; i < length; i++){
      setDigit(t[start + i], i, c);
  }
}

void RGBDigit::reColorSegment(unsigned int digit, byte segment, uint32_t c){
  if(segmentLit(digit, segment)){
    setSegment(digit, segment, c);
  }
}

void RGBDigit::reColorSegment(unsigned int digit, byte segment, byte red, byte green, byte blue){
  reColorSegment(digit, segment, Color(red, green, blue));
}

void RGBDigit::RGBDigit::reColor(byte red, byte green, byte blue){
  reColor(Color(red, green, blue));
}

void RGBDigit::reColor(uint32_t c){
  unsigned int nDigits = numPixels() << 3;
  for(unsigned int digit=0; digit < nDigits; digit++){
    reColor(digit, c);
  }
}

void RGBDigit::reColor(unsigned int digit, byte red, byte green, byte blue){
  reColor(digit, Color(red, green, blue));
}

void RGBDigit::reColor(unsigned int digit, uint32_t c){
  setPattern(_pixelMap[digit], digit, c);
}

void RGBDigit::enableAutoShow(){
  _autoShow = true;
  show();
}

void RGBDigit::disableAutoShow(){
  _autoShow = false;
}
