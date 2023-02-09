/*
 * File:   Led button.c
 * Author: ELCOT
 *
 * Created on 3 February, 2023, 8:47 PM
 */


#include <xc.h>
#include "Led button.h"
#define __XTAL_FREQ 20000000
 
void main(void) {
    TRISCbits.RC1 = 1;
    TRISDbits.RD0 = 0;
    TRISEbits.RE2 = 0;
    
    if(PORTCbits.RC1 == 0)
    {
     
       PORTDbits.RD0 = 1;
       PORTEbits.RE2 = 0;
  
    }
    if(PORTCbits.RC1 == 1)
    {
        PORTDbits.RD0 = 0;
        PORTEbits.RE2 = 1;
     }
        
    return;
}
