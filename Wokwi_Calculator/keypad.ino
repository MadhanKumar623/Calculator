#include "keypad.h"

extern volatile char *row, *col;
extern char expression[30],index,num1[10],num2[10],rough,temp,temp1,symbol;
extern long N1, N2;

void getKey()
{
  for(char i = 0;i<4;i=(i+1)%4){   //scanning each rows
    *row = (1<<i);
    if((*row&1)==1){
      if((*col&1)==1) {
        while((*col&1)==1); sendData('1');
        expression[index++] = '1';
      }
      else if((*col&2)==2){
         while((*col&2)==2); sendData('2');
         expression[index++] = '2';
      } 
      else if((*col&4)==4){
        while((*col&4)==4); sendData('3');
        expression[index++] = '3';
      }
       else if((*col&8)==8) {
        while((*col&8)==8); sendData('+');
        expression[index++] = '+';
       }
    }
    if((*row&2)==2){
      if((*col&1)==1) {
        while((*col&1)==1); sendData('4');
        expression[index++] = '4';
      }
      else if((*col&2)==2){
         while((*col&2)==2); sendData('5');
         expression[index++] = '5';
      } 
      else if((*col&4)==4){
        while((*col&4)==4); sendData('6');
        expression[index++] = '6';
      }
       else if((*col&8)==8) {
        while((*col&8)==8); sendData('-');
        expression[index++] = '-';
      }
    }
    if((*row&4)==4){
      if((*col&1)==1) {
        while((*col&1)==1); sendData('7');
        expression[index++] = '7';
      }
      else if((*col&2)==2){
         while((*col&2)==2); sendData('8');
         expression[index++] = '8';
      } 
      else if((*col&4)==4){
        while((*col&4)==4); sendData('9');
        expression[index++] = '9';
      }
       else if((*col&8)==8) {
        while((*col&8)==8); sendData('x');
        expression[index++] = 'x';
       }
    } 
    if((*row&8)==8){
      if((*col&1)==1) {
        while((*col&1)==1);
        clearLcd();
        loop();
      }
      else if((*col&2)==2){
         while((*col&2)==2); sendData('0');
         expression[index++] = '0';
      } 
      else if((*col&4)==4){
        while((*col&4)==4); return;
      }
       else if((*col&8)==8) {
        while((*col&8)==8); sendData('/');
        expression[index++] = '/';
      }
    }
    else delay1(1);   
  }
}


void convertToIntegers()
{
  char k=0;
  N1 = 0; N2 = 0;
  for(char i=rough-2;i>=0;i--){
      N1 = N1 + power(num1[i],k);
      k++;
  }
  k = 0;
  for(char i=temp1-1;i>=0;i--){
     N2 = N2 + power(num2[i],k);
     k++;
  }
  return;
}

void split_numbers()
{
  temp = 0; temp1 = 0; 
  while((expression[temp]!='+')&&(expression[temp]!='-')&&(expression[temp]!='x')&&(expression[temp]!='/')){
     num1[temp] = expression[temp];
     temp++;
  }
  symbol = expression[temp];
  num1[temp++] = '$';
  rough = temp;
  if(!isdigit(expression[temp])) loop(); 
  while(expression[temp]!='$'){
    num2[temp1] = expression[temp];
    temp++;
    temp1++;
  }
  num2[temp1] = '$'; 
  return;
}