#ifndef PRINT_H
#define PRINT_H

#include "usart.h"

void print_hex(int value);
void print_int(int value);
void print_double(double value);
void print_str(char *s, int len);

#endif