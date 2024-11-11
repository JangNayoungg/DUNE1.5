/*
* raw(?) I/O
*/
#ifndef _IO_H_
#define _IO_H_

#include "common_ny.h"

KEY get_key(void);
void printc(POSITION pos, char ch, int color);
void gotoxy(POSITION pos);
void set_color(int color);

#endif

