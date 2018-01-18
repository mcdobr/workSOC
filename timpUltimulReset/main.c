#include<iom16.h>
#include<inavr.h>

__no_init unsigned int nr_ovf;
__no_init unsigned int timer1_val;

#pragma vector=TIMER1_OVF_vect
__interrupt void timer1_ovf_isr()
{
  ++nr_ovf;
}

int main( void )
{
  TCNT1 = 0;
  TCCR1B |= (1 << CS10);
  TIMSK |= (1 << TOIE1);
  __enable_interrupt();
  
  if (MCUCSR & (1 << EXTRF)) {
  
    unsigned long long perioada = timer1_val + 1LL * nr_ovf * 0xFFFF;
    perioada *= 0.00025; // in ms
    
    nr_ovf = 0;
    timer1_val = 0;
    
  }
  
  while(1) {
    timer1_val = TCNT1;
  }
  
  return 0;
}
