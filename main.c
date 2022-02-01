#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
//
volatile int MSB = 0;
volatile int LSB = 0;
volatile int encoded = 0;
volatile int last_encoded = 0;
volatile int counter;
ISR(INT1_vect, ISR_ALIASOF(INT0_vect));

ISR(INT0_vect)
{
	cli();
	MSB = (1 << PIND2)&PIND;
	LSB = (1 << PIND3)&PIND;
	encoded = MSB | LSB;

	int sum  = (last_encoded << 2) | (encoded >> 2);

	if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) counter ++;
	if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) counter --;
	last_encoded = encoded;
	sei();
}



int main(void)
{
	cli();
	EICRA = 0;
	EICRA |= (1 << ISC00) | (1 << ISC01)  | (1 << ISC10) | (1 << ISC11);
	EIMSK |= (1 << INT0) | (1 << INT1);
	DDRD = 0x00;
	sei();
	while (1)
	{
		
	}
	return 0;
}
