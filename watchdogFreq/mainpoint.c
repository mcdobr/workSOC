/* 1.Sa se calculeze si afiseze pe serial
in format x.xxx frecventa WatchDog cu WDP2-0:100. */


#include <inavr.h>
#include <iom16.h>
#include "usart.h"
#include "print.h"

__no_init long wd_time;

int main( void )
{
  const int TIMER1_PRESCALER = 64;
  const int CPU_CYCLES_USEC = 4;
  const long WATCHDOG_TIMEOUT_NO_CYCLES = 262144;
  
  /* seteaza prescalerul cerut la watchdog, init timer1, usart */
  WDTCR |= (1 << WDP2);
  TCCR1B = (1 << CS11) | (1 << CS10);
  //usart_init(BAUD_RATE);
  
  /* printeaza rezultatele de dinainte de reset */
  wd_time *= TIMER1_PRESCALER / CPU_CYCLES_USEC;
  
  double wd_period = 1.0 * wd_time / WATCHDOG_TIMEOUT_NO_CYCLES;
  double wd_freq = 1.0 / wd_period; // in megahertz
  print_double(wd_freq);
  
  
  WDTCR |= (1 << WDE);
  TCNT1 = 0;
  __watchdog_reset();
  
  
  while (1) {
    wd_time = TCNT1;
  }
  return 0;
}
