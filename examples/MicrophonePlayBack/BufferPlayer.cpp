/*

  Blocking buffer player using the 
  CS43L22 codec class for Arduino STM32GENERIC

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
#include "Arduino.h"
#include "BufferPlayer.h"
#include "CS43L22_STM32.h"
#include "I2S.h"

I2SClass I2S(SPI3, PC12 /*sd*/ , PA4 /*ws*/, PC10 /*ck*/, PC7/* MCK*/); // setup for STM32F4 Discovery, check your board schematic

CS43L22_STM32 Codec;

#define AUDIOCODEC_CS PD4

BufferPlayer::BufferPlayer()
{

};

void BufferPlayer::begin(uint32_t samplingFrequency_Hz)
{
  SamplingFrequency=samplingFrequency_Hz;
  
  pinMode(AUDIOCODEC_CS, OUTPUT); // the chip select pin of the codec needs to be enabled

  // digitalWrite(AUDIOCODEC_CS, HIGH);
  // start I2S
  // I2S will also produce MCK for the codec of aroung 12Mhz
  // without MCK the CS43L22 is not working
  I2S.begin(I2S_PHILIPS_MODE, samplingFrequency_Hz, 16);

  digitalWrite(AUDIOCODEC_CS, HIGH); // enable codec
  Codec.begin();
}

#define DACZEROAMPLITUDE 0x4000
int Amplitude = 100;

// unsigned byte buffer player
void BufferPlayer::playBuffer(const uint8_t *table, uint32_t tableLength, float maxDuration_sec,  float speedFactor)
{
  uint32_t duration_ms = maxDuration_sec * 1000;
  float index = 0;

  uint32_t startTime = millis();
  while (millis() - startTime < duration_ms)
  {
    if (index < tableLength)
    {
      int dacValue = DACZEROAMPLITUDE + ((int)table[(int)index] - 128) * Amplitude;
      I2S.write(dacValue); // left channel
      I2S.write(dacValue); // right channel 
      index+=speedFactor;
    } else
    {
      I2S.write(DACZEROAMPLITUDE);
      I2S.write(DACZEROAMPLITUDE);
    }
  }
}
void BufferPlayer::playBuffer(const uint8_t *table, uint32_t tableLength)
{
  float maxDuration_sec = tableLength / SamplingFrequency;
  float speedFactor = 1;
  playBuffer(table, tableLength, maxDuration_sec, speedFactor );
}

// 16 bit buffer player
// table values: full scale range -32768..+32767
void BufferPlayer::playBuffer(int16_t *table, uint32_t tableLength, float maxDuration_sec,  float speedFactor)
{
  uint32_t duration_ms = maxDuration_sec * 1000;
  float index = 0;

  uint32_t startTime = millis();
  while (millis() - startTime < duration_ms)
  {
    if (index < tableLength)
    {
     
      uint16_t dacValue = (int32_t ) DACZEROAMPLITUDE*2 + table[(int)index];
      dacValue=dacValue>>1; // for unknown reaons the DAC goes only from 0..0x7FFF
      
      I2S.write(dacValue); // left channel
      I2S.write(dacValue); // right channel 
      index += speedFactor;
    } else
    {
      I2S.write(DACZEROAMPLITUDE);
      I2S.write(DACZEROAMPLITUDE);
    }
  }

}

void BufferPlayer::playBuffer(int16_t *table, uint32_t tableLength)
{
  float maxDuration_sec = tableLength / SamplingFrequency;
  float speedFactor = 1;
  playBuffer(table, tableLength, maxDuration_sec, speedFactor );
}


void BufferPlayer::end()
{
    digitalWrite(AUDIOCODEC_CS, LOW); // disable codec,  enough noise, stop it !!
}

void BufferPlayer::setVolume(uint8_t vol)
{
  Codec.setVolume(vol);
}

