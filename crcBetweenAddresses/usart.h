#ifndef USART_H
#define USART_H

#include <inavr.h>
#include <iom16.h>

#define F_CPU 4000000
#define BAUD 19200
#define BAUD_RATE (F_CPU/16/BAUD - 1)


void usart_init(unsigned int baud);
unsigned char usart_receive();
void usart_transmit(unsigned char data);

#endif