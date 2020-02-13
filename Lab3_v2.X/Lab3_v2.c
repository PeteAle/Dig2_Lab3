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
#include <stdlib.h>
#include <math.h>
#include "lib_adc.h"
#include "lib_osccon.h"
#include "LCDv1.h"

#define _XTAL_FREQ 4000000

uint8_t cuenta = 0;
uint8_t cuenta2 = 0;
float pot1 = 0;
float pot2 = 0;
uint16_t temp = 0, temp2 = 0;
uint16_t unid1 = 0, decen1 = 0, cent1 = 0, unid2 = 0, decen2 = 0, cent2 = 0;
unsigned char rxdata = 0;


void setup(void);
void intEnable(void);
void eusartTX8(void);
void eusartRX8(void);
void baudRate(void);

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
        lcd8_setCursor(1,1);
        delay_1ms2();
        lcd8_dispChar("S1:");
        delay_1ms2();
        lcd8_setCursor(1,6);
        delay_1ms2();
        lcd8_dispChar("S2:");
        delay_1ms2();
        lcd8_setCursor(1,11);
        delay_1ms2();
        lcd8_dispChar("S3:");
        delay_1ms2();
        // Envío de datos del Pot1 al LCD bajo S1.
        lcd8_setCursor(2,1);
        delay_1ms2();
        temp = ((pot1*5.0)/255.0)*100;
        cent1 = temp/100;
        temp = temp - (cent1*100);
        decen1 = temp/10;
        temp = temp - (decen1*10);        
        unid1 = temp;
        lcd8_dispNum(cent1);
        delay_1ms2();
        lcd8_dispChar(".");
        delay_1ms2();
        lcd8_dispNum(decen1);
        delay_1ms2();
        lcd8_dispNum(unid1);
        delay_1ms2();
        // Envío de datos del Pot2 a LCD bajo S2.
        lcd8_setCursor(2,6);
        delay_1ms2();
        temp2 = ((pot2*5.0)/255.0)*100;
        cent2 = temp2/100;
        temp2 = temp2 - (cent2*100);
        decen2 = temp2/10;
        temp2 = temp2 - (decen2*10);
        unid2 = temp2;
        lcd8_dispNum(cent2);
        delay_1ms2();
        lcd8_dispChar(".");
        delay_1ms2();
        lcd8_dispNum(decen2);
        delay_1ms2();
        lcd8_dispNum(unid2);
        delay_1ms2();
        // Verificación del RX.
        if (PIR1bits.RCIF == 1){
            rxdata = RCREG;
            lcd8_setCursor(2,11);
            delay_1ms2();
            if (rxdata == 1){
                cuenta += cuenta;
                
            }
        }
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
    PIE1bits.TXIE = 0;
    PIE1bits.RCIE = 1;
}

void eusartTX8(void){
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 0;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TRMT = 1;
}

void eusartRX8(void){
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.FERR = 0;
    RCSTAbits.OERR = 0;
    PIR1bits.RCIF = 0;
}

void baudRate(void){
    BAUDCTLbits.RCIDL = 0;
    BAUDCTLbits.SCKP = 0;
    BAUDCTLbits.BRG16 = 0;
    BAUDCTLbits.WUE = 0;
    BAUDCTLbits.ABDEN = 0;
    BAUDCTLbits.ABDOVF = 0;
    SPBRG = 6;
}