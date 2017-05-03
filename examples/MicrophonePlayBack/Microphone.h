/*

  MP45DT02 ST-MEMS audio sensor omni-directional digital microphone

  Bitbanging driver

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
#include <stdint.h>

class Microphone
{
  public:
    Microphone();
    void begin(uint32_t samplingFrequency_Hz);
    void record(int16_t *sampleBuffer, uint32_t bufferLength);
    uint32_t getSamplingFrequency();
  
  private:
    float    SamplingFrequency;
  
};
