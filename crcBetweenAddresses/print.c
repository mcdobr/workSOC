#include <stdio.h>
#include "print.h"

#define PRINT_BUFFER_LENGTH 10

static char str[PRINT_BUFFER_LENGTH];

void print_hex(int value)
{
  char *p;
  sprintf(str, "%x", value);
  
  for (p = str; *p != '\0'; ++p)
    usart_transmit(*p);
  
}

void print_int(int value)
{
  char *p;
  sprintf(str, "%d", value);
  
  for (p = str; *p != '\0'; ++p)
    usart_transmit(*p);
}

void print_double(double value)
{
  char *p;
  sprintf(str, "%lf", value);
  
  for (p = str; *p != '\0'; ++p)
    usart_transmit(*p);
}

void print_str(char *s, int len)
{
  int i;
  for (i = 0; i < len; ++i)
    usart_transmit(s[i]);
}