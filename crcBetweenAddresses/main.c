#include <stdio.h>
#include "crc.h"
#include "print.h"
#include "usart.h"

unsigned int start_address, stop_address;

void getAddresses()
{
  char c, str[20] = "0x422 0x424";
  /*
  int len = 0;
  while ((c = usart_receive()) != '$') {
    str[len++] = c;
  }
  */
  sscanf(str, "%x%x", &start_address, &stop_address);
  
}

int main( void )
{
  usart_init(BAUD_RATE);
  getAddresses();
  
  unsigned int my_crc = crc16_with_table(0, start_address, stop_address - start_address);
  unsigned int abc = crc16(CRC16_CCITT, 0, start_address, stop_address - start_address, MSBF);
  
  return 0;
}
