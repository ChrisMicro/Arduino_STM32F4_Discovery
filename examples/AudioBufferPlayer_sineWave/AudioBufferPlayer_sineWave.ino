/*
  playing a sine wave with different volumes

  Framework used: Arduino compatiple STM32GENERIC 
  Hardware:       STM32F4 Discovery

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

#include "BufferPlayer.h"

#define SAMPLINGFREQUENCY 16000
#define WAVEBUFFERLENGTH  SAMPLINGFREQUENCY * 1 // 1 seconds

BufferPlayer Player;

int16_t wave_i16[WAVEBUFFERLENGTH];

void setup()
{
  Player.begin( SAMPLINGFREQUENCY );

  float   frequency = 440;
  float   amplitude = 100;
  // calculate buffer values for test tone
  for ( int n = 0; n < WAVEBUFFERLENGTH; n++ ) wave_i16[n] = ( sin( 2 * PI * frequency / SAMPLINGFREQUENCY * n )) * 0x7FFF;
}

void loop()
{
  Player.setVolume(100);
  Player.playBuffer(wave_i16 , WAVEBUFFERLENGTH);

  Player.setVolume(50);
  Player.playBuffer(wave_i16 , WAVEBUFFERLENGTH);

}
