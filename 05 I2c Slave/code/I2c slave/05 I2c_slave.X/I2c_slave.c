/*
 * File:   I2c_slave.c
 * Author: User
 *
 * Created on February 11, 2023, 12:16 PM
 */


#include <xc.h>
#include "I2c_slave.h"
#define _XTAL_FREQ 4000000 // Fosc
unsigned char RX_Data = 0x00;
//-----------[ Functions' Prototypes ]--------------
void I2C_Slave_Init(unsigned char);
//==================================================
void main(void)
{
  TRISD = 0x00;
  PORTD = 0x00;
  I2C_Slave_Init(0x40); // Initiate I2C Slave With Address = 64 or 0x40
  while(1)
  {
 
  }
  return;
}
//----------------[ END OF MAIN ]-------------------
//==================================================
void __interrupt() ISR(void)
{
  if(SSPIF)
  {
    if(!R_nW) // Slave Write (Receive)
    {
      char Dummy = SSPBUF; // Dummy Read
      CKP = 1; // Release The SCL Clock Line
      while(!BF); // Wait Until Completion
      RX_Data = SSPBUF; // Read The Buffer Data
      PORTD = RX_Data;  // Output The Received Byte
    }
  CKP = 1;   // Release The SCL Clock Line
  SSPIF = 0; // Clear The Interrupt Flag
  }
}
//---------------[ I2C Routines ]-------------------
void I2C_Slave_Init(unsigned char Address)
{
  //---[ Configures The I2C In Slave Mode]---
  SSPADD = Address; // Set The I2C Slave Device Address
  SSPSTAT = 0x80;
  SSPCON1 = 0x36;
  SSPCON2 = 0x01;
  TRISC3 = 1; // SCL Set To Input
  TRISC4 = 1; // SDA Set To Input
  GIE = 1;    // Enable Interrupts
  PEIE = 1;
  SSPIF = 0;
  SSPIE = 1;
}