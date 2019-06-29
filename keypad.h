#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "TM4C123.h"                    // Device header

void keypad_init(void);
char get_keypad(void);

#endif
