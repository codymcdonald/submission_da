/*
 * CPE301_DA2C_task3.c
 *
 * Created: 3/20/2019 2:27:21 AM
 * Author : Cody
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

//declare vital variables
int matchCount = 0;
int dc60 = 27; //overflow count to reach 6796 ov count 27
int dc40 = 18; //overflow count to reach 4530 ov count 18
int flag = 1;  //flag used to toggle between duty cycles
int cycleMatch = 255;	//compare to 255 and clear each time

//0.725s period
//60% = 0.435s. TCNT = 6796 = 1A8C
//40% = 0.29s. TCNT = 4530 = 11B2

int main(void)
{
	DDRB |= (1<<2)|(1<<5);			// Set all PORTB out
	PORTB |= (1<<5);		//turn off LED 5
	TCCR0A |= (1<<WGM01);	//set ctc mode on OCRA
	TCCR0B |= (1<<CS00)|(1<<CS02);	// Set pre-scaler to 1024
	TIMSK0 |= (1<<OCIE0A);	//enable compare interrupts
	OCR0A = cycleMatch;
	sei();					//enable interrupts
	
	while(1);				//infinite loop
	
}

ISR(TIMER0_COMPA_vect){
		matchCount ++;
		if (flag == 1 && matchCount == dc40){
			PORTB &= ~(1<<2);	//toggle LED
			matchCount = 0;	//reset overflow counter
			flag = 0;
		}
		else if (flag == 0 && matchCount == dc60){
			PORTB |= (1<<2);	//toggle LED
			matchCount = 0;	//reset overflow counter
			flag = 1;
		}
}