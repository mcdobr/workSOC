// se cere generarea unei frecvente de 20Hz cu duty=33% cu prescaler 8 pe timer1

// Voi da semnalul pe OC1A

void timer1_init()
{
  /*
  Mod fast PWMM cu comparare cu ICR1
  Prescaler 8 adică  CS12-0: 001
  nu știu dacă e nevoie să setez COMA1 și sau COMA0
  */
  
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);
  
  
  
  
}

int main()
{
  // Dau semnalul pe OC1A (adica PD5)
  DDRD |= (1 << PD5);
  
  // Setez ICR1 ca perioada unui ciclu al semnalului generat
  // si OCR1 ca numarul de cicli pe high
  ICR1 = 25000;
  OCR1A = ICR1 / 100 * 33;
  
  timer1_init();
  
  while (1);
  
  return 0;
}