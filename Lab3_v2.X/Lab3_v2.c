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
#include <stdio.h>
#include "lib_adc.h"
#include "lib_osccon.h"
#include "LCDv1.h"

#define _XTAL_FREQ 4000000

unsigned char pot1 = 0;
unsigned char pot2 = 0;
float pot1_val = 0;
float pot2_val = 0;
char datos[10];

void setup(void);
void intEnable(void);

void __interrupt() isr(){
    di();
    if (PIR1bits.ADIF == 1 && ADCON0bits.CHS3 == 1 && ADCON0bits.CHS2 == 0 && ADCON0bits.CHS1 == 0 && ADCON0bits.CHS0 == 0){
        pot1 = ADRESH;
        PIR1bits.ADIF = 0;
    }
    else if (PIR1bits.ADIF == 1 && ADCON0bits.CHS3 == 1 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 0 && ADCON0bits.CHS0 == 1){
        pot2 = ADRESH;
        PIR1bits.ADIF = 0;
    }
    if (ADCON0bits.CHS3 == 1 && ADCON0bits.CHS2 == 0 && ADCON0bits.CHS1 == 0 && ADCON0bits.CHS0 == 0){
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;
    }
    else if (ADCON0bits.CHS3 == 1 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 0 && ADCON0bits.CHS0 == 1){
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;
    }
    ei();
}

void main(void){
    setup();
    oscInt(1);
    lcd8_init2();
    adcSetup();
    analogInSel(8);
    adcFoscSel(1);
    intEnable();
    while(1){
        if (ADCON0bits.GO_DONE != 1){
            ADCON0bits.GO_DONE = 1;
        }
        lcd8_cmd(0x80);
        delay_1ms2();
        lcd8_display("S1:");
        delay_1ms2();
        pot1_val = (pot1*5.0)/255;
        lcd8_cmd(0xC0);
        delay_1ms2();
        sprintf(datos, "%.1f", pot1_val);
        lcd8_display(datos);
        delay_1ms2();
    }
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
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

void intEnable(void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
}