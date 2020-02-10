/*
 * File:   lib_osccon.c
 * Author: Peter
 *
 * Created on January 30, 2020, 8:07 PM
 */

#include <xc.h>
#include "lib_osccon.h"

unsigned char oscInt(unsigned char freq) {
    switch(freq){
        case 0:     // Oscilador de 8 MHz
            OSCCONbits.IRCF2 = 1;
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF0 = 1;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 1:     // Oscilador de 4 MHz
            OSCCONbits.IRCF2 = 1;
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF0 = 0;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 2:     // Oscilador de 2 MHz
            OSCCONbits.IRCF2 = 1;
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF0 = 1;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 3:     // Oscilador de 1 MHz
            OSCCONbits.IRCF2 = 1;
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF0 = 0;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 4:     // Oscilador de 500 kHz
            OSCCONbits.IRCF2 = 0;
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF0 = 1;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 5:     // Oscilador de 250 kHz
            OSCCONbits.IRCF2 = 0;
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF0 = 0;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 6:     // Oscilador de 125 kHz
            OSCCONbits.IRCF2 = 0;
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF0 = 1;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 1;
            OSCCONbits.LTS = 0;
            OSCCONbits.SCS = 1;
            break;
        case 7:     // Oscilador de 31 kHz
            OSCCONbits.IRCF2 = 0;
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF0 = 0;
            OSCCONbits.OSTS = 0;
            OSCCONbits.HTS = 0;
            OSCCONbits.LTS = 1;
            OSCCONbits.SCS = 1;
            break;
    }
    return(freq);
}