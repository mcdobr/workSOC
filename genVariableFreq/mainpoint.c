/** Frecvenţa semnalului iniţială este de 1kHz. Factorul de umplere este de 50%.
 * Utilizând terminalului la trimiterea caracterului “+” frecvenţa va crește cu
 * 1kHz, iar la trimiterea caracterului “-“ frecvenţa va scade cu 1kHz intervalul 
 * de variaţie fiind [1kHz,10kHz]. Factorul de umplere trebuie să rămână la 50%
 */

// oare îmi trebuie un flag gen must_change_freq care sa-l folosesc in while?
 
#include "usart.h"

#define MIN_FREQ 1
#define MAX_FREQ 10
#define FREQ_STEP 1
#define CPU_CYCLES_PER_KHZ 4000

unsigned int freq_khz = 1;
unsigned char must_change_freq_flag = 0;

#pragma vector=USART_RXC_vect
__interrupt void usart_rxc_isr()
{
  if (UDR == '+' && freq_khz < MAX_FREQ)
    freq_khz += FREQ_STEP;
  else if (UDR == '-' && freq_khz > MIN_FREQ)
    freq_khz -= FREQ_STEP;
}

void timer1_init()
{
  /* WGM = Fast PWM cu TOP = ICR1
   * fara prescaler
   * semnalul il dau pe OC1A(PD5)
   * clear oc1b on compare match, set on top
   */
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);
  TCNT1 = 0;
}

int main()
{
  // Initial semnalul e 1
  DDRD |= (1 << PD5);
  PORTD |= (1 << PD5);
  
  // Initializare resurse
  usart_init(BAUD_RATE);
  timer1_init();
  
  __enable_interrupt();
  while (1) {
    ICR1 = CPU_CYCLES_PER_KHZ / freq_khz;
    OCR1A = ICR1 / 2;
  }
  return 0;
}