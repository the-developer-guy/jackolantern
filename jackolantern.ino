/*
The Developer Guy
Digital jack-o'-lantern
Videos can be found here:
  https://vid.me/EtfWs
  https://youtu.be/ierrFn5CT3c

2 LEDs to flicker
And one PIR sensor to detect motion.

If left alone the device will shout on the next bypasser
but will continue flickering if in the center of attention.
*/

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// candle effect
void flicker();

DFRobotDFPlayerMini myDFPlayer;
uint8_t brightness;
int led1 = 5;
int led2 = 6;
int pirInput = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pirInput, INPUT);
  myDFPlayer.begin(Serial); 
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  // Check if someone appears
  if(digitalRead(pirInput) == HIGH)
  {
    myDFPlayer.next();
    while(digitalRead(pirInput) == HIGH) // avoid early retrigger
    {
      flicker();
    }
    delay(1000);
  }
}

void flicker()
{
  // set an initial PWM value first and 
  brightness = 128;
  for(uint16_t i = 0; i < 1000; i++)
  {
    analogWrite(led1, brightness);        
    brightness += random(-20, 20);
    analogWrite(led2, brightness);        
    brightness += random(-20, 20);
    delay(10);
  }
  // finally turn off the LEDs
  analogWrite(led1, 0);
  analogWrite(led2, 0);
}

