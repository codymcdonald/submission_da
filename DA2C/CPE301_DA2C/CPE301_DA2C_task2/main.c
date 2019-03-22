/*
 * CPE301_DA2C_task2.c
 *
 * Created: 3/20/2019 2:00:02 AM
 * Author : Cody
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

//declare vital variables
int ovFlowCount = 0;
int dc60 = 27; //overflow count to reach 6796 ov count 27
int dc40 = 18; //overflow count to reach 4530 ov count 18
int flag = 1;

//0.725s period
//60% = 0.435s. TCNT = 6796 = 1A8C
//40% = 0.29s. TCNT = 4530 = 11B2

int main(void)
{
	DDRB |= (1<<2)|(1<<5);		// Set all PORTB out
	PORTB |= (1<<5);
	TCCR0B |= (1<<CS00)|(1<<CS02);	// Set pre-scaler to 1024
	TIMSK0 |= (1<<TOIE0); //enable timer interrupts
	sei(); //enable interrupts
	TCNT0 = 0; //initialize clock
	
	while(1);
	
}

ISR(TIMER0_OVF_vect){
		ovFlowCount ++;
		if (flag == 1 && ovFlowCount == dc40){
			PORTB &= ~(1<<2);
			ovFlowCount = 0;	//reset overflow counter
			flag = 0;
		}
		else if (flag == 0 && ovFlowCount == dc60){
			PORTB |= (1<<2);
			ovFlowCount = 0;	//reset overflow counter
			flag = 1;
		}
}