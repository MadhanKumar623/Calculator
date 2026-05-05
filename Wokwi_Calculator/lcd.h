#ifndef LCD_H
#define LCD_H

void clearLcd(void);
void sendData(char);
void sendString(char*);
void controlF(void);
void out_inst(char);
void init_lcd(void);

#endif


