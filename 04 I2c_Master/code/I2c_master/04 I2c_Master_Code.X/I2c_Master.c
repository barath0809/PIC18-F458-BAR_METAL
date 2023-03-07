/*
 * File:   I2c_main.c
 * Author: User
 *
 * Created on February 11, 2023, 12:08 PM
 */


#include <xc.h>
#include "I2c_master.h"
#define _XTAL_FREQ 4000000 // Fosc
#define I2C_BaudRate 100000 // I2C Baud Rate = 100 Kbps
//----------------------------------------------------------
//-----------------[ Functions' Prototypes ]----------------
void I2C_Master_Init(void);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Write(unsigned char Data);
//----------------------------------------------------------
void main()
{
  TRISB = 0xFF;
  TRISD = 0x00;
  PORTD = 0x00;
  unsigned char i=1;
  I2C_Master_Init();
  while(1)
  {
    I2C_Start(); // I2C Start Sequence
    I2C_Write(0x40); // I2C Slave Device Address + Write
    I2C_Write(i++); // The Data To Be Sent
    I2C_Stop(); // I2C Stop Sequence
    __delay_ms(500);
    RD3 = ~RD3; // Toggle LED Each Time A Byte Is Sent!
  }
}
//------------[ END OF MAIN ]--------------
//-----------------------------------------
void I2C_Master_Init()
{
  SSPCON1 = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
  TRISC3 = 1;
  TRISC4 = 1;
}
void I2C_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Start()
{
  //---[ Initiate I2C Start Condition Sequence ]---
  I2C_Wait();
  SEN = 1;
}
void I2C_Stop()
{
  //---[ Initiate I2C Stop Condition Sequence ]---
  I2C_Wait();
  PEN = 1;
}
void I2C_Restart()
{
  //---[ Initiate I2C Restart Condition Sequence ]---
  I2C_Wait();
  RSEN = 1;
}
void I2C_ACK(void)
{
  //---[ Send ACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 0; // 0 -> ACK, 1 -> NACK
  ACKEN = 1; // Send ACK Signal!
}
void I2C_NACK(void)
{
  //---[ Send NACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 1; // 1 -> NACK, 0 -> ACK
  ACKEN = 1; // Send NACK Signal!
}
unsigned char I2C_Write(unsigned char Data)
{
  //---[ Send Byte, Return The ACK/NACK ]---
  I2C_Wait();
  SSPBUF = Data;
  I2C_Wait();
  return ACKSTAT;
}
 