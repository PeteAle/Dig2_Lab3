/*
 * File:   Lab3_v2.c
 * Author: Peter
 *
 * Created on February 6, 2020, 11:08 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
//#include "lib_adc.h"
//#include "lib_osccon.h"
#include "LCDv1.h"

#define _XTAL_FREQ 4000000

void setup(void);

void __interrupt() isr(){
    
}

void main(void){
    setup();
    lcd8_init2();
    lcd8_display("PINCHE PIRUJA");
    lcd8_cmd(0xC0);
    lcd8_display("CHINGUESE");
    while(1);
}

void setup(void){
    TRISA = 0x00;
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00;
    ANSEL = 0x00;
    ANSELHbits.ANS13 = 1;
    ANSELHbits.ANS8 = 1;
    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

