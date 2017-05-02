/*
  accelerometer controlls sound pitch and repetion rate

  Framework used: Arduino compatiple STM32GENERIC
  Hardware:       STM32F4 Discovery
  codec:          CS43L22 Audio DAC
  accelerometer:  LIS302DL or LIS3DSH
                  ( depends on the verison of the STM32F4 Discovery board )

*************************************************************************************

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

********************************** list of outhors **********************************
  v0.1  2.Mai.2017 C. ChrisMicro  initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something
  2017 ChrisMicro
*************************************************************************************
*/

#include "LIS3DSx.h"
#include "BufferPlayer.h"
#include "wavetables.h"

#define SERIALINTERFACE SerialUSB

LIS3DSx Accelerometer;
BufferPlayer Player;


#define NUMLEDS 4
const uint8_t Led[] = {LED_GREEN, LED_ORANGE, LED_RED, LED_BLUE};

void setLed(uint8_t n, uint8_t state)
{
  if(n==4)digitalWrite(Led[n], !state);
  else digitalWrite(Led[n], state);
}

void setup()
{
  //SERIALINTERFACE.begin(115200);

  delay(1000);

  //SERIALINTERFACE.println("\n accelerometer");

  // print sensor informatiion
  Accelerometer.begin();
  Player.begin(16000);
  for (int n = 0; n < NUMLEDS; n++)  pinMode(Led[n], OUTPUT);

}

uint8_t LedCounter=0;
void loop()
{
  //SERIALINTERFACE.print(" X: "); SERIALINTERFACE.print  ( Accelerometer.getX_g() );
  //SERIALINTERFACE.print(" Y: "); SERIALINTERFACE.print  ( Accelerometer.getY_g() );
  //SERIALINTERFACE.print(" Z: "); SERIALINTERFACE.println( Accelerometer.getZ_g() );

  //SERIALINTERFACE.print(" abosolute acceleration: "); SERIALINTERFACE.println( Accelerometer.absolute_g() );

  //delay(500);
  float duration;
  float randomSpeedFactor;

  duration = 0.1 + abs(Accelerometer.getX_g());
  randomSpeedFactor = 0.05 + abs(Accelerometer.getZ_g());
  
  //SERIALINTERFACE.print("duration"); SERIALINTERFACE.print(duration);
  
  if ( Accelerometer.getZ_g() > 0 ) Player.playBuffer(piano , SONGLEN, duration, randomSpeedFactor);
  else                              Player.playBuffer(sabine, SONGLEN, duration, randomSpeedFactor);

  setLed(LedCounter++,0);
  
  if(LedCounter>3)LedCounter=0; 
  setLed(LedCounter,1);

}



