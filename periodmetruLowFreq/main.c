/* timer2 il folosesc ca sa masor perioada
 * timer0 ca sa trimit din secunda in secunda rezultatul pe seriala
 */

#include <iom16.h>
#include <inavr.h>

#define NR_TIMER2_OVFS_IN_SECOND 16

unsigned long nr_timer0_ovf = 0;
unsigned long nr_timer2_ovf = 0;
unsigned long perioada;

#pragma vector=INT0_vect
__interrupt void int0_isr()
{
  perioada = (nr_timer2_ovf * 0xFF + TCNT2) / 4;
  
  nr_timer2_ovf = 0;
  TCNT2 = 0;
}

#pragma vector=TIMER2_OVF_vect
__interrupt void timer2_ovf_isr()
{
  ++nr_timer2_ovf;
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_isr()
{
  ++nr_timer0_ovf;
  if (nr_timer0_ovf >= NR_TIMER2_OVFS_IN_SECOND) {
  }
}

int main( void )
{
  /* Enable int externa pe INT0, pe frontul pozitiv */
  GICR |= (1 << INT0);
  MCUCR |= (1 << ISC01) | (1 << ISC00);
  
  /* Seteaza timere: T0 prescaler 1024, T2 fara prescaler */
  TCCR0 |= (1 << CS02 ) | (1 << CS00);
  TCCR2 |= (1 << CS20);
  
  TIMSK |= (1 << TOIE0) | (1 << TOIE2);
  TCNT0 = TCNT2 = 0;
  
  /* Seteaza flag-ul global de interrupt */
  __enable_interrupt();
  
  
  while (1) {
  }
  
  return 0;
}
