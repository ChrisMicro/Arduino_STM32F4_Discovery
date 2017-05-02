/*

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
#include <Wire.h>

class CS43L22_STM32
{
  public:
    CS43L22_STM32();
    void begin();
    void setVolume(uint8_t vol);
};

