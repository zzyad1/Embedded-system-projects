/*
 * main_project.c
 *
 *  Created on: Feb 3, 2024
 *      Author: zyadm
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char secound = 0 , min=0 ,hour =0;

ISR(INT2_vect)
{
	TCCR1B = (1<<WGM12) | (1<<CS11)| (1<<CS10);
}

void inti_int2 (void)
{

	DDRB &= (~(1<<PB2));
	PORTB |=(1<<PB2);

	SREG =SREG & ~(1<<7);
	GICR |=(1<<INT2);
	MCUCSR |= (1<<ISC2);
	SREG =SREG |(1<<7);

}

ISR(INT1_vect)
{
	TCCR1B =(~(1<< CS10)) & (~(1<< CS11)) & (~(1<< CS12));
}

void inti_int1(void)
{
	SREG &= ~(1 << 7);
	GICR |= (1 << INT1);
	MCUCR = (1 << ISC11)|(1 << ISC10);
	SREG |= (1 << 7);
	DDRD &= (~(1 << PD3));
}


ISR(INT0_vect)
{
	secound = 0 , min=0 ,hour =0;
}
void init_int0 (void)
{
	SREG =SREG &~(1<<7);
	GICR =GICR|(1<<INT0);
	MCUCR =MCUCR |(1<<ISC01);
	SREG =SREG |(1<<7);
	DDRD &=~(1<<PD2);
	PORTD |=(1<<PD2);
}


ISR(TIMER1_COMPA_vect)
{
	secound++;
	if ( secound == 60)
	{
	   secound = 0;
	   min++;
	}
	if (min == 60)
	{
		min = 0;
		hour++;
	}
	if (hour == 24)
	{
		secound =0;
		min =0;
		hour = 0;
	}


}

void Timer1_inti (void)
{
	TCNT1 =0;
	TIMSK |= (1<<OCIE1A);
	OCR1A =15624;
	TCCR1A =(1<<FOC1A) | (1 << COM1A1);
	TCCR1B = (1<<WGM12)| (1<<CS11)| (1<<CS10);
}

int main(void)
{
	DDRA = 0x3f;
    PORTA = 0x3f;
	DDRC |= 0x0F;
	PORTC &= 0xF0;
	SREG |= (1 << 7);

	init_int0 ();
	inti_int1();
	inti_int2 ();
	Timer1_inti();
	while (1)
	{
		PORTA = 0x20;
		PORTC = (PORTC & 0xF0) | ((secound % 10) & 0x0F);
		_delay_ms(0.1);
		PORTA = 0x10;
		PORTC = (PORTC & 0xF0) | ((secound / 10) & 0x0F);
		_delay_ms(0.1);
		PORTA = 0x08;
		PORTC = (PORTC & 0xF0) | ((min % 10) & 0x0F);
		_delay_ms(0.1);
		PORTA = 0x04;
		PORTC = (PORTC & 0xF0) | ((min / 10) & 0x0F);
		_delay_ms(0.1);
		PORTA = 0x02;
		PORTC = (PORTC & 0xF0) | ((hour % 10) & 0x0F);
		_delay_ms(0.1);
		PORTA = 0x01;
		PORTC = (PORTC & 0xF0) | ((hour / 10) & 0x0F);
		_delay_ms(0.1);
	}
}


