/*
 * File:   Led.c
 * Author: ELCOT
 *
 * Created on 2 February, 2023, 10:14 PM
 */


#include <xc.h>
#include "led.h"
#define _XTAL_FREQ 20000000

void main(void) {
    TRISB = 0x00;
    while(1)
    {
        PORTB = 1;
        __delay_ms(100);
        PORTB = 0;
        __delay_ms(100);
        
    }
    return;
}
