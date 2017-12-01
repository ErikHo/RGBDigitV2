/*
(C) Erik Homburg 2017

Application of 4 RGBDigits connected to an Arduino Uno
using the RGBdigitV2 library.

This software is based on Schield_count_4_RGBDigit_demo
by RGBDigit < http://rgbdigit.com >
by Coen   RGBDigit  Version One_digit_alpa_num_V15.01.01

Required is the Adafruit_Neopixel class. Use the
Arduino IDE library manager or get it at
https://github.com/adafruit/Adafruit_NeoPixel

This example code is in the public domain.
*/

                                             
#include <RGBDigitV2.h>

#define PIN 12  // Sending neopixel data to Pin 12 

RGBDigit myDigits(4,PIN); 4 digit display

enum colorSchemeType{earth, water, fire, air, justRed, boring, wild};

colorSchemeType colorScheme[]={earth, water, air, fire, boring, wild, boring, justRed};



byte Bright = 150; 
byte k;
byte m;
int count = 0;

void setup(){

  myDigits.begin();
  myDigits.clearAll();                  // Initialize all pixels to 'off'
  myDigits.setBrightness(Bright);      	// For safety (to prevent too high of a power draw), the test case defaults to 40
  delay(500);                           // sanity check delay - allows reprogramming if accidently blowing power w/leds
  m = sizeof(colorScheme)/ sizeof(colorScheme[0]);
  k = 0;
}

//----------Main loop---------------------------------------------------------------------------

void loop() { 

  char txt[5];
  count= 0;

  while (count < 25 ){

    count++;                          // increment count
    sprintf(txt,"%4d",count); 

    myDigits.disableAutoShow();

    myDigits.setText(txt, 0, 4, 40, 40, 40);
    for (int digit = 0; digit < 4; digit++){
       paintDigit(digit, colorScheme[k]);   
    }

    myDigits.enableAutoShow();
    delay(50);
  }
  
  // cycle through the color schemes
  k++;
  if(k >= m){
    k = 0;  
  }
  
}  // end of main loop


// get a next color from one of the possible color schemes
uint32_t getColorFromScheme(colorSchemeType s){
  byte z;
  switch (s){
    case earth:
      z = random(100);
      return myDigits.Color(25 + (z * 63)/100, 13 + (z * 12)/100, 1 + (z * 3 )/100);
    break;
    case water:
      return myDigits.Color(0, 130, random(10,200)); 
    break;
    case fire:
      return myDigits.Color(100, random(10,100), 0);
   break;
    case air:
      z = random(8 ,128);
      return myDigits.Color(z, z, 128); 
    break;
   case justRed:
      return 0x800000;
    break;
    case boring:
      return 0x202020;
    break;
    case wild:
    default:
      return myDigits.Color(random(1, 200), random(1,200), random(1, 200));
    break;    
  }
}

// recolor the segments of a digit
void paintDigit(unsigned int digit, colorSchemeType t){
  for(int segment = 0; segment < 8; segment++){
    myDigits.reColorSegment(digit, segment, getColorFromScheme(t));
  }
}         



