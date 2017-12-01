/*
(C) Erik Homburg 2017

Application of a single RGBDigit connected to an Arduino Uno

This software is based on Schield_count_1_RGBDigit_demo
created 2017   by RGBDigit < http://rgbdigit.com >
by Coen   RGBDigit  Version One_digit_alpa_num_V15.01.01

Required is the Adafruit_Neopixel class. Use the
Arduino IDE library manager or get it at
https://github.com/adafruit/Adafruit_NeoPixel
 
This example code is in the public domain.
*/
                                       
#include <RGBDigitV2.h>

#define PIN 12                // Sending neopixel data to Pin 12 

RGBDigit myDigits(4,PIN);     //4 digit display

int colorScheme[]={0, 1, 2, 3, 5, 6, 5, 4};

byte Bright = 100; 
byte k;
byte m;
int count = 0;

void setup(){

  myDigits.begin();
  myDigits.clearAll();                  // Initialize all pixels to 'off'
  myDigits.setBrightness(Bright);      	// For safety (to prevent too high of a power draw), the test case defaults to 40
  delay(500);                           // sanity check delay - allows reprogramming if accidently blowing power w/leds
  m = sizeof(colorScheme)/ sizeof(colorScheme[0]); // number of color schemes
  k = 0;
}

//----------Main loop---------------------------------------------------------------------------

void loop() { 

  count= 0;
  
  while (count < 10 ){
    
    myDigits.disableAutoShow();              // disable pixel updates
    
    myDigits.setDigit(count, 0, 40, 40, 40); // write a digit
    paintDigit(0, colorScheme[k]);           // change the color of the segments 
    
    myDigits.enableAutoShow();               // enable pixel updates
    
    count++;                                 // increment count    
    delay(200);
  }
  
  // cycle through the color schemes
  k++;
  if(k >= m){
    k = 0;  
  }
  
}  
//---------end main loop----------------------------------------------------------------------

// get a next color from one of the possible color schemes
uint32_t getColorFromScheme(int s){
  byte z;
  switch (s){
    case 0:
      z = random(100);
      return myDigits.Color(25 + (z * 63)/100, 13 + (z * 12)/100, 1 + (z * 3 )/100);
    break;
    case 1:
      return myDigits.Color(0, 130, random(10,200)); 
    break;
    case 2:
      return myDigits.Color(100, random(10,100), 0);
   break;
    case 3:
      z = random(8, 128);
      return myDigits.Color(z, z, 128); 
    break;
   case 4:
      return 0x800000;
    break;
    case 5:
      return 0x202020;
    break;
    case 6:
    default:
      return myDigits.Color(random(1, 200), random(1, 200), random(1, 200));
    break;    
  }
}

// recolor the segments of a digit
void paintDigit(unsigned int digit, int t){
  for(int segment = 0; segment < 8; segment++){
    myDigits.reColorSegment(digit, segment, getColorFromScheme(t));
  }
}         

