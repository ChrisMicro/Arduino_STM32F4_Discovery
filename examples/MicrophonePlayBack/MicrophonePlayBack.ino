/*

  MP45DT02 ST-MEMS audio sensor omni-directional digital microphone

  Framework used: Arduino compatiple STM32GENERIC
  Hardware:       STM32F4 Discovery
  codec:          CS43L22 Audio DAC
  accelerometer:  LIS302DL or LIS3DSH
                  ( depends on the verison of the STM32F4 Discovery board )
                  MP45DT02 ST-MEMS audio sensor omni-directional digital microphone

  Remark: very preliminary version, 
          microphone class to be reworked for better sound quality

*************************************************************************************
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
********************************** list of outhors **********************************
  v0.1  3.Mai.2017 C. ChrisMicro  initial, crued implementation. Better filters needed

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something
  2017 ChrisMicro
*************************************************************************************
*/

#include "Microphone.h"
#include "BufferPlayer.h"

#define SAMPLINGFREQUENCY 16000
#define WAVEBUFFERLENGTH  SAMPLINGFREQUENCY * 1 // 1 seconds

Microphone   Mic;
BufferPlayer Speaker;

int16_t wave_i16[WAVEBUFFERLENGTH]={0};

void setup()
{
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  pinMode(USER_BTN, INPUT);

  Mic.begin(SAMPLINGFREQUENCY);
  Speaker.begin( SAMPLINGFREQUENCY );
}

void loop()
{

  // repeat to play sound
  digitalWrite(LED_BLUE, HIGH);
  
  while (!digitalRead(USER_BTN))   Speaker.playBuffer(wave_i16 , WAVEBUFFERLENGTH);
  
  digitalWrite(LED_BLUE, LOW);

  // record sound
  digitalWrite(LED_GREEN, HIGH);
  
  Mic.record(wave_i16 , WAVEBUFFERLENGTH);
  
  digitalWrite(LED_GREEN, LOW);

}
