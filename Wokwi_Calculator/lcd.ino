#include "lcd.h"

extern volatile char *out,*control;

void clearLcd()  
{
  *out = 1;
  *control = 0;
  delay1(2);
  *control = 1;
  delay1(2);
  *control = 0;
  delay1(2);
}

void sendData(char stringData)
{
  *out = stringData;
  *control = 2;  
  delay1(1);
  *control = 3;
  delay1(1);
  *control = 2;
  delay1(1);
}

void sendString(char *ptr)
{
   while(*ptr!=NULL){
      sendData(*ptr);
      ptr++;
   }
}

void controlF()
{
   *control = 0x00;
   delay1(1);
   *control = 0x01;
   delay1(1);
   *control = 0x00;
   delay1(1);
}

void out_inst(char outInst)
{
   *out = outInst;  //always send control signal after sending the data first
   controlF();
}

void init_lcd()     //initialising LCD instructions
{
   out_inst(60); //8 bit data - 5*11 and 2 lines display
   out_inst(15); //display and cursor and cursor blink
   out_inst(6); //increment of AC (i.e) cursor moving direction
}



