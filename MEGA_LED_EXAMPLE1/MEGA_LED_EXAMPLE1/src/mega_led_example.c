// Code for HW2
#include <asf.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

void delay75(void){
	// sub routine of 750ms delay
	_delay_ms(750);
}

int main(void){
	/* Set PORTC.3 for input*/
	DDRC &= ~(1 << 3);
	PORTC |= (1 << 3);
	/* set PORTB.5 for output*/
	DDRB |= (1<<5);
	PORTB |= (1<<5);	// pull up activated.
	/* PD2 as input */
	DDRD &= ~(1<<2); // PD.2 as an input
	PORTD |= 1<<2;//pull-up activated
	EIMSK |= (1<<INT0);//enable external interrupt 0
	sei();//enable interrupts
	while(true){
		if((PINC & 0x8) != 0x8){
			PORTB |= (1 << 5);
			_delay_ms(1250);	// 1.25s delay
		}
		else{
			PORTB &= ~(1 << 5);
		}
	}
}

ISR (INT0_vect)//ISR for external interrupt 0
{
	//sets B1 to 1
	PORTB |= (1<<5);
	//0.5s delay
	_delay_ms(500);
	//sets B1 to 0
	PORTB &= (0<<5);
}
