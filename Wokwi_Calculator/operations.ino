#include "stdio.h"
#include "operations.h"

extern char result[10], symbol;

long power(char a,char b)
{
  long x = 1;
  a = a - 48;
  for(char i=0;i<b;i++)
    x = x*10;
  return (a*x);
}

void calculate()
{
  switch(symbol){
    case '+': sprintf(result,"%ld",N1+N2);
              out_inst(0xC0);
              sendString(result); 
              break;
    case '-': sprintf(result,"%ld",N1-N2);
              out_inst(0xC0);
              sendString(result); 
              break;
    case 'x': sprintf(result,"%ld",N1*N2);
              out_inst(0xC0);
              sendString(result); 
              break;
    case '/': if(N2==0)
              {
                out_inst(0xC0);
                sendString("   MATH ERROR   ");
              }
              else
              {
                double y = (double)N1/N2;
                dtostrf(y,16,16,result);
                out_inst(0xC0);
                sendString(result);
             }
             break;
    default: sendString("INVALID INPUTS");
             break;
  }
  return;
}