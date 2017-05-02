/*
  MEMS driver
  
  accelerometer:  LIS302DL or LIS3DSH

  MEMS digital output motion sensor:
  ultra-low-power high-performance three-axis "nano" accelerometer

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
#include <SPI.h> 
#include <math.h>

#include "LIS3DSx.h"

#define SERIALINTERFACE SerialUSB

#define CS PE3

void accelerometer_SPI_select()
{
  digitalWrite(CS, LOW); // 0=SPI communication mode, 1=SPI IDLE MODE
  delayMicroseconds(50);
}

void accelerometer_SPI_release()
{
  digitalWrite(CS, HIGH);
  delayMicroseconds(50);
}

#define READREGISTERCOMMAND 0x80
uint8_t spiRead(uint8_t registerAddress)
{
  uint8_t r;
  
  accelerometer_SPI_select();
  SPI.transfer( registerAddress | READREGISTERCOMMAND );
  delayMicroseconds(500);
  r =  SPI.transfer(0); // dummy write, data read
  delayMicroseconds(500);
  accelerometer_SPI_release();
  
  return r;
}

void LIS3DSx::begin()
{
    // configure SPI
  pinMode(CS, OUTPUT);

  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  
  // configure sensor
  accelerometer_SPI_select();
  SPI.transfer(0x20); // CTRL4 ODR register
  delay(10);
  SPI.transfer(0x47); // 25 Hz update, enable x,y,z
  accelerometer_SPI_release(); 
}

int16_t LIS3DSx::getX()
{
  int32_t a,aa;
  int16_t ag;
  
  a= spiRead  ( 0x28 );
  aa = spiRead( 0x29 );
  
  return (a + (aa << 8));
}

int16_t LIS3DSx::getY()
{
  int32_t a,aa;
  int16_t ag;
  
  a= spiRead  ( 0x2A );
  aa = spiRead( 0x2B );
  
  return (a + (aa << 8));
  
}

int16_t LIS3DSx::getZ()
{
  int32_t a,aa;
  int16_t ag;
  
  a= spiRead  ( 0x2C );
  aa = spiRead( 0x2D );
  
  return (a + (aa << 8));
}

#define ONE_G 16384

float LIS3DSx::getX_g()
{
  return getX()/(float)ONE_G;
}

float LIS3DSx::getY_g()
{
  return getY()/(float)ONE_G;
}

float LIS3DSx::getZ_g()
{
  return getZ()/(float)ONE_G;
}

float LIS3DSx::absolute_g()
{
  float g;
  g=sqrt(getX_g()*getX_g()+getY_g()*getY_g()+getZ_g()*getZ_g());
  return g;
}


uint8_t LIS3DSx::getChipVersion()
{
  uint8_t whoAmI=spiRead(0x0F);
  return whoAmI;
}


