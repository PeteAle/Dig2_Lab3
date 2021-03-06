/*
 * File:   Lab3_v1.c
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
#include "lib_adc.h"
#include "lib_osccon.h"

#define _XTAL_FREQ 4000000

#define lcd_rs PORTCbits.RC0
#define lcd_rw PORTCbits.RC1
#define lcd_en PORTCbits.RC2
#define lcd_data PORTA

int cont = 0;
char disp = 0;

void setup(void);
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_write(unsigned char data);
void lcd_display(char *value);
void poll_flag(void);
void delay_1ms(void);


void __interrupt() isr(){
    
}

void setup(void);

void main(void) {
    setup();
    lcd_init();
    lcd_display("PROBANDO");
    lcd_cmd(0xC0);
    lcd_display("ESTA MIERDA");
    while(1);
    return;
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

void delay_1ms(void){
    for (int i = 0; i < 50; i++);
}

void lcd_init(void){
    __delay_ms(20);
    lcd_cmd(0x30);
    __delay_ms(5);
    lcd_cmd(0x30);
    __delay_ms(1);
    lcd_cmd(0x30);
    __delay_ms(1);
    lcd_cmd(0x38);
    lcd_cmd(0x10);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x0C);
    lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cmd){
    poll_flag();
    lcd_data = cmd;
    lcd_rs = 0;
    lcd_rw = 0;
    lcd_en = 1;
    delay_1ms();
    lcd_en = 0;
}

void lcd_write(unsigned char data){
    poll_flag();
    lcd_data = data;
    lcd_rs = 1;
    lcd_rw = 0;
    lcd_en = 1;
    delay_1ms();
    lcd_en = 0;
}

void lcd_display(char *value){
    while(*value){
        lcd_write(*value++);
    }
}

void poll_flag(void){
    lcd_rs = 0;
    lcd_rw = 1;
    lcd_en = 0;
    delay_1ms();
    lcd_en = 1;
    if (PORTAbits.RA7 == 1){
        lcd_en = 0;
        delay_1ms();
        lcd_en = 1;
    }
}

void intEnable(void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
}

