#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include<avr/interrupt.h>

int eightBitValue;
int main(void)
{
  ADCSRA|=1<<ADPS2;
  ADMUX|=1<<ADLAR;
  ADMUX|=1<<REFS0;
  ADCSRA|=1<<ADIE;
  ADCSRA|=1<<ADEN;

  sei();
  
  ADCSRA|=1<<ADSC;
  
  int UBRR_Value=25;
  UBRR0H=(int)(UBRR_Value>>8);
  UBRR0L=(int)(UBRR_Value);
  UCSR0B=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C=(1<<USBS0)|(3<<UCSZ00);
  while(1)
  {
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0=eightBitValue;
  }
}
ISR(ADC_vect)
{
  eightBitValue=ADCH;
  ADCSRA|=1<<ADSC;
}
