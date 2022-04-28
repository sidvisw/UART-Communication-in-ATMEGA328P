#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
int duty;
int main(void)
{
  DDRD|=1<<PORTD6;
  TCCR0A|=(1<<COM0A1)|(1<<WGM00)|(1<<WGM01);
  TIMSK0|=1<<TOIE0;

  sei();
  
  TCCR0B|=(1<<CS00);
  
  int UBRR_Value=25;
  UBRR0H=(int)(UBRR_Value>>8);
  UBRR0L=(int)(UBRR_Value);
  UCSR0B=(1<<RXEN0);
  UCSR0C=(1<<USBS0)|(3<<UCSZ00);

  int recieveData;
  while(1)
  {
    while(!(UCSR0A&(1<<RXC0)));
    recieveData=UDR0;
    OCR0A=recieveData;
    _delay_ms(100);
  }
}
