/*  
RGBDigitV2 demonstration sketch

(c) Erik Homburg 2017

Possibilities of the RGBDigitV2 library are 
demonstrated on a 4 digit RGBDigit
( http://www.rgbdigit.com ) display connected
to an Arduino Uno.
See https://github.com/ErikHo/RGBDigitV2

Required is the Adafruit_Neopixel class. Use the
Arduino IDE librairy manager or get it at
https://github.com/adafruit/Adafruit_NeoPixel

This example code is in the public domain.
*/


#include <RGBDigitV2.h>

// some HTML color definitions
#define  rgb_Gold                   0xFFD700
#define  rgb_Violet                 0xEE82EE
#define  rgb_Indigo                 0x4B0082
#define  rgb_Blue                   0x0000FF
#define  rgb_Green                  0x008000
#define  rgb_Red                    0xFF0000


#define NDIGITS 4
RGBDigit myDigits(NDIGITS, 12);   // use 4 digits and pin 12

// all characters, note that an "&"" is not valid and wil show as
// three horizontal bars.
char allChars[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,'&',
                   'A','B','C','D','E','F','G','H','I','J',
                   'K','L','M','N','O','P','Q','R','S',
                   'T','U','V','W','X','Y','Z','&',
                   '0','1','2','3','4','5','6','7','8','9',
                   ' ','-','_','(',')','*'};

void setup() {
  
  // initialize myDigits
  myDigits.begin();
  
  //clear all digits
  myDigits.clearAll();

  // setBrightness and getBrightness are inherited from Adafruit_NeoPixel  
  if (myDigits.getBrightness() < 255){
    myDigits.setBrightness(255);
  }
}

void loop() {

  myDigits.clearAll();

  // Show all characters with a "ticker" banner
  int m = sizeof(allChars) - NDIGITS + 1;
  for (int i = 0; i < m; i++){
    myDigits.setText(allChars, i, NDIGITS, rgb_Gold);
    delay(250);
  }
  delay(1000);
  // speedy shift text back, color in rgb format 
  for (int i = m; i >= 0 ; i--){
    myDigits.setText(allChars, i, NDIGITS, 128, 128, 128);
    delay(125);
  }
  delay(1000);

  // Set a dot using different possible color formats
  myDigits.clearAll();
  myDigits.setDot(0, 255, 0, 0);
  myDigits.setDot(1, 0xFF0000);
  myDigits.setDot(2, rgb_Red);
  myDigits.setDot(3, myDigits.Color(255, 0, 0));

    delay(1000);
  // Clear the dots
  myDigits.clearDot(0);
  myDigits.setDot(1, 0);
  myDigits.setDot(2, 0, 0, 0);
  myDigits.setDot(3, myDigits.Color(0, 0, 0));
  delay(1000);

  // Display a number
  char pi[] = "3142";
  
  myDigits.setText(pi, 0, NDIGITS, rgb_Violet);
  myDigits.setDot(0, rgb_Violet);
  delay(1000);
  // Set first and last digit to green
  myDigits.reColor(0, 0, 128, 0);
  myDigits.reColor(3, rgb_Green);
  delay(1000);
  // Set all digits to green
  myDigits.reColor(rgb_Green);
  delay(1000);
  
  // show the number again
  // do the same without reColor
  myDigits.setText(pi, 0, NDIGITS, rgb_Violet);
  delay(1000);
   // Set first and last digit to red
  myDigits.setDigit(pi[0], 0, rgb_Red);
  myDigits.setDigit(pi[3], 3, rgb_Red);
  delay(1000);
  // Set all digits to red  
  myDigits.setText(pi, 0, NDIGITS, rgb_Red);
  delay(1000);

  // show the number again
  myDigits.setText(pi, 0, NDIGITS, rgb_Violet);
  delay(1000);

  // If a segment is lit, change segment to blue, else set to dark orange
  myDigits.disableAutoShow(); // disable auto pixel update

  for(int digit = 0; digit < NDIGITS; digit++){
    for(int segment = 0; segment < 8; segment++){
      if(myDigits.segmentLit(digit, segment)){
        myDigits.setSegment(digit, segment, rgb_Blue);
      }
      else{
        myDigits.setSegment(digit, segment, 38, 18, 0);
      }
    }
  }
  myDigits.show();           // update pixels, enableAutoShow however does this anyway
  myDigits.enableAutoShow(); // enable auto pixel update
  delay(1000);

  // write user defined patterns directly, make an animation
  byte mover[]{
    B00001000,
    B01011100,
    B00111111,
    B01100011,
    B00000001,
    B00000000
  };

  myDigits.clearAll();
  
  // 10 sequences of a moving box in digit 0
  
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < sizeof(mover); j++){
      myDigits.setPattern(mover[j], 0, rgb_Indigo);
      delay(100);
    }
  }
  delay(1000);

}
