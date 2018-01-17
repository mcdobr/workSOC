
#include "usart.h"

void usart_init(unsigned int baud)
{
  UBRRH = (unsigned char)(baud >> 8);
  UBRRL = (unsigned char)(baud & 0xFF);
  
  /* Enable rx si tx */
  UCSRB = (1 << RXEN) | (1 << TXEN);
  
  /* Seteaza 8 biti de date */
  UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
  
}

unsigned char usart_receive()
{
  while (!(UCSRA & (1 << RXC)));
  return UDR;
}

void usart_transmit(unsigned char data)
{
  while (!(UCSRA & (1 << UDRE)));
  UDR = data;
}