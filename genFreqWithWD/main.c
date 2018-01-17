#include <inavr.h>
#include <iom16.h>

//100ms perioada... adica 0,25usec * x = 100 ms
// => x = 10^2 ms / 0,25 usec = 10
//66 ms pe 1
//34 ms pe 0
// o să fac output pe PD3 
enum state_t {HIGH, LOW};

__no_init enum state_t state;


int main( void )
{
  const int PRESCALER = 64;
  
  DDRD |= (1 << PD5);
  /*TCCR1B |= (1 << CS11) | (1 << CS10);
  TCNT1 = 0;
  */
  
  if (state == HIGH) {
    PORTD |= (1 << PD5);
    
    // Trebuie să mai adaug cicli cât pt 1.5 ms cu ajutorul TCNT1
    //while (TCNT1 < 1000);
    
    // setez prescaler pt 32.5 ms
    WDTCR &= ~((1 << WDP2) | (1 << WDP1) | (1 << WDP0));
    WDTCR |= (1 << WDP0);
    
    state = LOW;
  } else {
    PORTD &= ~(1 << PD5);
    
    // Trebuie să mai adaug cicli cât pt 1.0 ms cu ajutorul TCNT1
    //while (TCNT1 < 750);
    
    // setez prescaler pt 65 ms
    WDTCR &= ~((1 << WDP2) | (1 << WDP1) | (1 << WDP0));
    WDTCR |= (1 << WDP1);
    
    state = HIGH;
  }
  
  
  WDTCR |= (1 << WDE);
  while (1);
  
  return 0;
}
