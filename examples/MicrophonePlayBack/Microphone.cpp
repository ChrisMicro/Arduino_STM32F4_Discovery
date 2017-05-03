// https://www.theunterminatedstring.com/probing-pdm/
/*

  MP45DT02 ST-MEMS audio sensor omni-directional digital microphone

  Bitbanging driver

*************************************************************************************
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
********************************** list of outhors **********************************
  v0.1  3.Mai.2017 C. ChrisMicro  initial, crude implementation. Better filters needed

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something
  2017 ChrisMicro
*************************************************************************************
*/

#include "Arduino.h"
#include "Microphone.h"

#define MICROPHON_CLK_INPUT            PB10
#define MICROPHON_PDMDATA_OUTPUT        PC3

Microphone::Microphone()
{

};

int32_t  OldValue;

uint32_t PDM_BitsPerSample;

#define  AFACTOR 0.9

#define TESTBUFFERLENGTH 10000

void multiplyFactor(int16_t *x, uint32_t signalLength, float factor)
{
  for (int i = 4; i < signalLength; i++)
  {
    x[i] = x[i] * factor;
  }
}

void Microphone::record(int16_t *sampleBuffer, uint32_t bufferLength)
{
  int32_t  FloatingMeanBuffer[256] = {0};
  int32_t  n, k;
  int32_t  sample = 0;
  uint32_t startTime;
  float    meanvalue;
  int32_t  value;
  int32_t  amplitude = 10;

  int32_t  average = 0;
  uint32_t index = 0;

  meanvalue = 0;
  value = 0;

  startTime = micros();

  // start sampling signal
  for (n = 0; n < bufferLength; n++)
  {

    for (k = 0; k < PDM_BitsPerSample; k++)
    {
      digitalWrite(MICROPHON_CLK_INPUT, LOW);
      if (digitalRead(MICROPHON_PDMDATA_OUTPUT) == 0) value++;
      else value--;
      // CIC
      average += value;
      average -= FloatingMeanBuffer[index];
      FloatingMeanBuffer[index] = value;
      index++;
      index &= 0x3F;

      digitalWrite(MICROPHON_CLK_INPUT, HIGH);
    }
    // high pass
    //sample = value - OldValue;
    //OldValue = value;

    meanvalue = AFACTOR * meanvalue + (1 - AFACTOR) * value;
    sample = value - meanvalue;

    sampleBuffer[n] = sample;
  }

  uint32_t duration_us = micros() - startTime;

  SamplingFrequency = bufferLength / ( (float) duration_us / 1e6 );

  multiplyFactor(sampleBuffer , bufferLength, 20);
}


void Microphone::begin(uint32_t samplingFrequency_Hz)
{
  pinMode( MICROPHON_CLK_INPUT, OUTPUT );
  pinMode( MICROPHON_PDMDATA_OUTPUT, INPUT );

  OldValue = 0;
  SamplingFrequency = 0;
  PDM_BitsPerSample = 250;

  int16_t testBuffer[TESTBUFFERLENGTH];

  record(testBuffer, TESTBUFFERLENGTH );

  float correctionFactor = SamplingFrequency / samplingFrequency_Hz;
  PDM_BitsPerSample = PDM_BitsPerSample * correctionFactor;
}

uint32_t Microphone::getSamplingFrequency()
{
  return SamplingFrequency;
}




