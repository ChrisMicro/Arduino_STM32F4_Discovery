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
#include <stdint.h>

typedef struct {
  uint8_t * signalBuffer;
  uint32_t signalBufferLength;
} SampleBuffer_t;

class BufferPlayer
{
  public:
    BufferPlayer();
    void begin(uint32_t samplingFrequency_Hz);
    void playBuffer(const uint8_t *table, uint32_t tableLength, float duration_sec,  float speedFactor);
    void playBuffer(const uint8_t *table, uint32_t tableLength);
    void playBuffer(int16_t *table, uint32_t tableLength, float duration_sec,  float speedFactor);
    void playBuffer(int16_t *table, uint32_t tableLength);
    void end();
    void setVolume(uint8_t vol);
    
  private:
    uint32_t SamplingFrequency;

};
