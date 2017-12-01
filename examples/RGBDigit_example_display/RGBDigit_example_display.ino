/*  
    RGBDigit display example sketch
    Adapted from Crützen 2015
    This software is in the public domain
    (C) Erik Homburg 2017
    
    Example of a possible clock front end
    using the RGBDigitV2 class
*/


// original example from GitHub RGBDigit adapted to the RGBDigitV2 class

//Required is the Adafruit_Neopixel class. Use the
//Arduino IDE library manager or get it at
//https://github.com/adafruit/Adafruit_NeoPixel

#include <RGBDigitV2.h>

#define nDigits 4                 // 4 digit display
RGBDigit rgbDigit(nDigits);       // uses default pin 12

byte hour = 11;
byte minute = 21;
byte day = 4;
byte month = 10;
unsigned int year = 2017;

void setup() {
  rgbDigit.begin();
  rgbDigit.clearAll();
}

void loop() {
  showTimeDate();
  wooosh();
}

void showTimeDate() {
  int h = hour;
  rgbDigit.setDigit(h / 10, 0, 64, 0, 0); // show on digit 0 (=first). Color is rgb(64,0,0).
  rgbDigit.setDigit(h % 10, 1, 64, 0, 0);
  int m = minute;
  rgbDigit.setDigit(m / 10, 2, 0, 0, 64);
  rgbDigit.setDigit(m % 10, 3, 0, 0, 64);
  rgbDigit.setDot(1, 64, 64, 64);    // show dot on digit 1 (=second). Color is rgb(64,0,0).
  rgbDigit.clearDot(3);               // clear dot on digit 3 (=fourth)
  delay(5000);

  int d = day;
  rgbDigit.setDigit(d / 10, 0, 64, 64, 0);
  rgbDigit.setDigit(d % 10, 1, 64, 64, 0);
  m = month;
  rgbDigit.setDigit(m / 10, 2, 0, 64, 64);
  rgbDigit.setDigit(m % 10, 3, 0, 64, 64);
  rgbDigit.setDot(1, 64, 64, 64);
  rgbDigit.setDot(3, 64, 64, 64);
  delay(2500);

  char textBuf[4]; 
  sprintf(textBuf,"%4d",year);   // print year value to char array
  rgbDigit.setText(textBuf, 0, nDigits, 1, 1, 1);
  rgbDigit.clearDot(1);
  rgbDigit.clearDot(3);
  fade();
}

void wooosh() {
  int delayVal = 100;
  for (int d = 0; d < nDigits; d++) {
      rgbDigit.setSegment(d, 4, 255 - 64*d, 64*d, 0);
      rgbDigit.setSegment(d, 5, 255 - 64*d, 64*d, 0);
      delay(delayVal);
      rgbDigit.clearDigit(d);
      rgbDigit.setSegment(d, 0, 255 -64*d, 64*d, 0);
      rgbDigit.setSegment(d, 3, 255 -64*d, 64*d, 0);
      rgbDigit.setSegment(d, 6, 255 -64*d, 64*d, 0);
      delay(delayVal);
      rgbDigit.clearDigit(d);
      rgbDigit.setSegment(d, 1, 255 - 64*d, 64*d, 0);
      rgbDigit.setSegment(d, 2, 255 - 64*d, 64*d, 0);
      delay(delayVal);
      rgbDigit.clearDigit(d);
    }
}

void fade()
{
  delay(1000);

  for (int c = 2; c < 32; c = c + 2) {
    rgbDigit.reColor(c, 1, 1);
    delay(1);
  }
  for (int c = 2; c < 32; c = c + 2 ) {
    rgbDigit.reColor(31, c, 1);
    delay(1);
  }
  for (int c = 2; c < 32; c = c + 2) {
    rgbDigit.reColor(31, 31, c);
    delay(1);
  }
  for (int c = 31; c >= 1; c = c -2) {
    rgbDigit.reColor(31, c, 31);
    delay(1);
  }
  for (int c = 31; c >= 1; c = c - 2) {
    rgbDigit.reColor(c, 1, 31);
    delay(1);
  }
  for (int c = 31; c >= 1; c = c -2) {
    rgbDigit.reColor(1, 1, c);
    delay(1);
  }


}

