/*  RGBDigit text example sketch
    Copyright (C) 2017 Erik Homburg    
    Copyright (C) 2015 Ralph Crützen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

// original example from GitHub RGBDigit adapted to the RGBDigitV2 class

//Required is the Adafruit_Neopixel class. Use the
//Arduino IDE library manager or get it at
//https://github.com/adafruit/Adafruit_NeoPixel


#include <Arduino.h>

#include <RGBDigitV2.h>

// If necessary, change the number of digits in the next line
#define nDigits 4                 // 4 display digits 
RGBDigit rgbDigit(nDigits);       // uses default pin 12
//RGBDigit rgbDigit(nDigits, 6);  // uses another pin; 6 in this example

String text = "3 - 2 - 1 _ The quick brown fox jumps (over) the lazy dog";

void setup() {
  
  rgbDigit.begin();
  rgbDigit.clearAll();
  
  for (int i = 0; i < nDigits; i++){
   text = ' ' + text + ' ';
  }
}

void loop() {
  for (int i = 0; i < (text.length() - nDigits); i++) {
    rgbDigit.setText(text, i, nDigits, 255, 32, 16);
    delay(250);
  }
}


