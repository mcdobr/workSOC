#include "usart.h"
#include "crc.h"


int main(void)
{
  /* IAR pune crc-ul în ultimii 2 bytes */
  unsigned int crc16_len = 0x3FFE;
  unsigned int crc32_len = 0x3FFC;
  
  
  unsigned int iar_crc16 = *(__flash int*)crc16_len;
  unsigned int my_crc16 = crc16(CRC16_CCITT, 0, 0, crc16_len, MSBF);
  unsigned int my_crc16_with_table = crc16_with_table(0, 0, crc16_len);
  
  
  /*
  unsigned long iar_crc32 = *(__flash long*)crc32_len;
  unsigned long my_crc32 = crc32(CRC32, 0, 0, crc32_len, MSBF);
  unsigned long my_crc32_with_table = crc32_with_table(0, 0, crc32_len);
  */
  
  return 0;
}
