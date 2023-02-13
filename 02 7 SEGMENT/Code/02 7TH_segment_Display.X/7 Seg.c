/*
 * File:   7 Seg.c
 * Author: User
 *
 * Created on February 2, 2023, 3:03 PM
 */


#include <xc.h>
#include "7 seg.h"
#define _XTAL_FREQ 20000000

void ms_Delay(int Delay)// To create the delay function
{
   int i;
   while(Delay){
     for(i=0;i<1000;i++);
     Delay--;
   }
}

void main(void) 
{
    TRISC=0x00;
    int array[]={63,6,91,79,102,109,125,7,127,111};
    int i=0;
    while(1)
    {
        for(i=0;i<10;i++)
        {
         PORTC = array[i];
         ms_Delay(100);
//        PORTC ^=(1<<i);
//        ms_Delay(50);
//        i++;
       // if(i==9)
           // i=0;
        }
    }

    return;
}
