#ifndef CRC_H
#define CRC_H

#define CRC16_CCITT 0x1021
#define CRC32       0x04C11DB7
enum bit_order {LSBF, MSBF};

unsigned int crc16(unsigned int polinom, unsigned int init_val, 
                   unsigned int addr_start, unsigned int len, enum bit_order ord);
unsigned int crc16_with_table(unsigned int init_val, unsigned int addr_start, 
                              unsigned int len);
unsigned long crc32(unsigned long polinom, unsigned long init_val, unsigned int addr_start,
					unsigned int len, enum bit_order ord);
unsigned long crc32_with_table(unsigned long init_val, unsigned int addr_start,
							   unsigned int len);

extern __flash const unsigned int crc16_table[256];
extern __flash const unsigned long crc32_table[256];

#endif