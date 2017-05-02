/*
  read accelaration sensor and print serial

  Framework used: Arduino compatiple STM32GENERIC 
  Hardware:       STM32F4 Discovery
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

#define SERIALINTERFACE SerialUSB

LIS3DSx Accelerometer;

void setup()
{
  SERIALINTERFACE.begin(9600);

  delay(1000);

  SERIALINTERFACE.println("\n accelerometer");

  // print sensor informatiion
  Accelerometer.begin();
  
  uint8_t whoAmI = Accelerometer.getChipVersion();
  SERIALINTERFACE.print("WHO AM I register: ");  SERIALINTERFACE.print( whoAmI , HEX);

  if (whoAmI == 0x3B) SERIALINTERFACE.println("  LIS3DSL sensor detected ");
  if (whoAmI == 0x3F) SERIALINTERFACE.println("  LIS3DSH sensor detected ");

  SERIALINTERFACE.println("");
}

void loop()
{
  SERIALINTERFACE.print(" X: "); SERIALINTERFACE.print  ( Accelerometer.getX_g() );
  SERIALINTERFACE.print(" Y: "); SERIALINTERFACE.print  ( Accelerometer.getY_g() );
  SERIALINTERFACE.print(" Z: "); SERIALINTERFACE.println( Accelerometer.getZ_g() );

  SERIALINTERFACE.print(" abosolute acceleration: "); SERIALINTERFACE.println( Accelerometer.absolute_g() );
  
  delay(500);

}



