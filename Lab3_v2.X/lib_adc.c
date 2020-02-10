/*
 * File:   lib_adc.c
 * Author: Peter
 *
 * Created on February 5, 2020, 1:30 PM
 */


#include <xc.h>
#include "lib_adc.h"

void adcSetup(void){
    ADCON0bits.ADON = 1;
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
}

unsigned char analogInSel(unsigned char analogIn) {
    switch(analogIn){
        case 0:     // AN0
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
        case 1:     // AN1
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
        case 2:     // AN2
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
        case 3:     // AN3
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
        case 4:     // AN4
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
        case 5:     // AN5
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
        case 6:     // AN6
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
        case 7:     // AN7
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
        case 8:     // AN8
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
        case 9:     // AN9
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
        case 10:    // AN10
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
        case 11:    // AN11
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
        case 12:    // AN12
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
        case 13:    // AN13
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
    }
    return(analogIn);
}

unsigned char adcFoscSel(unsigned char fosc){
    switch(fosc){
        case 0:     // Fosc/2
            ADCON0bits.ADCS1 = 0;
            ADCON0bits.ADCS0 = 0;
            break;
        case 1:     // Fosc/8
            ADCON0bits.ADCS1 = 0;
            ADCON0bits.ADCS0 = 1;
            break;
        case 3:     // Fosc/32
            ADCON0bits.ADCS1 = 1;
            ADCON0bits.ADCS0 = 0;
            break;
    }
    return(fosc);
}
