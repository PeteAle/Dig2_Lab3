#include<htc.h>

#define RS RB6
#define EN RB7
#define D0 RC0
#define D1 RC1
#define D2 RC2
#define D3 RC3
#define D4 RC4
#define D5 RC5
#define D6 RC6
#define D7 RC7


#define _XTAL_FREQ 8000000
#include "lcd.h"



void main()
{
 int i;
  TRISB = 0x00;
  TRISC = 0x00;
  Lcd8_Init();
  while(1)
  {
    Lcd8_Set_Cursor(1,1);
    Lcd8_Write_String("electroSome LCD Hello World");
    for(i=0;i<15;i++)
    {
      __delay_ms(100);
      Lcd8_Shift_Left();
    }
    for(i=0;i<15;i++)
    {
      __delay_ms(100);
      Lcd8_Shift_Right();
    }
    Lcd8_Clear();
    Lcd8_Set_Cursor(2,1);
    Lcd8_Write_Char('e');
    Lcd8_Write_Char('S');
    __delay_ms(2000);
  }
}
