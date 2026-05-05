#include "port.h"
#include "lcd.h"
#include "operations.h"
#include "keypad.h"

extern char index, expression[30];

void setup() {
  init_port();
  set_port();
  init_lcd();
  sendString("   Welcome To   ");
  out_inst(0xC3);  //Instruction for moving to the second line and C3 is the address to which the cursor get moves
  sendString("CALCULATOR");
  delay1(450);
  clearLcd();
}

void loop() {
  index = 0;
  getKey();
  expression[index] = '$'; //symbol for End of each string
  split_numbers();
  convertToIntegers();
  calculate();
}
