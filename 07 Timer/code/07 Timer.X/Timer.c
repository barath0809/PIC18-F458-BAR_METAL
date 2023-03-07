
#include <xc.h>
#define _XTAL_FREQ 20000000

unsigned char i = 0;
int flag=0;

void main(void) {
    
   INTCON = 0xE0;
     T0CON = 0x80;
      TMR0 = 61 ; // 10 ms Delay
   TRISDbits.RD1 =0;
   
    while(1)
    {
            if(i == 0){
         PORTDbits.RD1 = 0;
            }
        if(i==100){
      PORTDbits.RD1 = 1;
        }  
      if(i==200){
          
          i=0;}
    }
    return;
}

void __interrupt()ISR1()
{
    GIE=0;
    if(TMR0IF)
    {
        i++;
        TMR0IF =0;
    }
    
  GIE=1;
     
}