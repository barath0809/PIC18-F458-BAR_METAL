/*
 * File:   ADC.c
 * Author: Barath kumar  s 
 *
 * Created on February 13, 2023, 2:47 PM
 */


#include <xc.h>
#include <stdio.h>
#include "ADC.h"
#define _XTAL_FREQ 20000000
void display(unsigned int a, unsigned int b);

void main(void) {
    TRISAbits.RA0 = 1; // Declare as the RA0 Analog mode read the data 
    TRISCbits.RC0 = 0;// To declare the pin as RS 
    TRISCbits.RC1= 0;// To declare as the port as the Enable
    TRISD = 0x00;    // To declare as PORTD(RD0 - RD7) as the Data output port
    long int var,my_adresh=0;
    float voltage=0;
    char array [10],volt[]={"Voltage:"};// To declare two array for the conversion store float values 
    ADCON0 = 0x01; // To declare as the 
    ADCON1 = 0x80; // To declare as the 
    display(0X38,0); // 8 bit data mode
    display(0X0c,0); // Display on cursor of 
    display(0X06,0); // Entry mode 
    display(0X01,0); // clear screen mode 
    while(1)
    {
            GODONE = 1; // To start the A/D Conversion 
            while(GO_nDONE); //Wait for A/D Conversion to complete
            my_adresh = ADRESH; // To store the High bit value as longint value
            var = ADRESL|(my_adresh<<8); // 10 bit data to 8 bit data conversion 
            voltage=  var *((float)5/(float)1023); // voltage conversion 
            sprintf(array,"%0.2f",voltage); // Convert to char array 
            display(0x80,0);  // Cursor control              
            for(int j=0;volt[j]!='\0';j++) // To print the string values
            {
               display(volt[j],1); // Call the function to print value
            }
            for(int i=0;i<4;i++) // To print the values live in A/D Conversion
            {
                display(array[i],1); // Function calling....
            }
            __delay_ms(100);
            //display(0X01,0);
    }
    return; 
}
void display(unsigned int a, unsigned int b) // This function is acess the values
{
    PORTD = a;
    PORTCbits.RC0 = b;
    PORTCbits.RC1 = 1;
      __delay_ms(10);
     PORTCbits.RC1 = 0;
     __delay_ms(10);
}
