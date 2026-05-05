#include "port.h"

volatile char *control,*out,*row,*col;

char num1[10],num2[10];
char expression[30];
char result[10];
char symbol;
char index = 0;
char temp = 0,temp1 = 0;
char rough = 0;

long N1 = 0, N2 = 0;

void delay1(int a) //a = 225 ---> 1 second 
{
   volatile long i; 
   while(a){
     for(i = 1;i<=1000;i++);
     a--;
   }
}

void init_port()
{
  //portF --> out
  //portK --> control
  //portA --> col
  //portD --> row
  char *dirF,*dirK,*dirA,*dirD;
  dirF = 0x30; dirK = 0x107;
  dirA = 0x21; dirD = 0x2A;
  *dirA = 0x00; *dirF = 0xFF;
  *dirK = 0xFF; *dirD = 0xFF;   
}

void set_port()
{
   col = 0x20; out = 0x31;
   row = 0x2B; control = 0x108;
}