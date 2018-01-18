/** Generati un semnal de 1kHz cu factor de umplere care variaza crescator si
 * descrescator, cu pasi de 5% intre 5 si 95% la fiecare 2 secunde si 
 * transmiterea factorului de umplere pe serial.
 */

#include <inavr.h>
#include <iom16.h>

#define MIN_DUTY  5
#define MAX_DUTY 95
#define DUTY_STEP 5

#define NR_OVF_IN_2SEC 2000
#define NR_CYCLES_PER_DUTY 4000

enum order_t {ASCENDING, DESCENDING};

unsigned int nr_ovf = 0;
unsigned char must_change_duty_flag = 0;

#pragma vector=TIMER1_OVF_vect
__interrupt void timer1_ovf_isr()
{
  ++nr_ovf;
  if (nr_ovf > NR_OVF_IN_2SEC) {
    nr_ovf = 0;
    must_change_duty_flag = 1;
  }
}

void timer1_init()
{
/**
 * folosesc timer1 cu modul fast PWM = 14 cu TOP LA OCR1A !!!!
 * clear OC1A on compare match, set oc1a at top
 * FOARTE IMPORTANT: Cand se ajunge la top se seteaza si TOVn interrupt flag
 *
 */
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);
  TIMSK |= (1 << TOIE1);
  
  TCNT1 = 0;
}

int main()
{
  unsigned int duty = MIN_DUTY;
  enum order_t order = ASCENDING;
  
  // Dau afara pe OC1A (PD5) si incepe cu 1
  DDRD |= (1 << PD5);
  PORTD |= (1 << PD5);
  
  // Setez numarul de cicli ai procesorului pt o perioada a semnalului de 1kHz
  ICR1 = NR_CYCLES_PER_DUTY;
  timer1_init();
  
  __enable_interrupt();
  while (1) {
    
    if (must_change_duty_flag) {
      //print(duty);
      OCR1A = ICR1 * duty / 100;
      must_change_duty_flag = 0;
      
      if (order == ASCENDING) {
        
        duty += DUTY_STEP;
        if (duty == MAX_DUTY)
          order = DESCENDING;
        
      } else {
        duty += DUTY_STEP;
        if (duty == MAX_DUTY)
          order = DESCENDING;
      }
    }
  }
  
  return 0;
}