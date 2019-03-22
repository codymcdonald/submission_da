/*
 * CPE301_DA2C_task1_p2.c
 *
 * Created: 3/19/2019 11:43:34 PM
 * Author : Cody
 */ 

#include <stdio.h>
#include <avr/io.h>

//TCNT FOR 1.25s = 19531.25. Overflow count = 77
int main(void){
	//initialize registers
	DDRB |= (1<<2)|(1<<5);		//set portb 2 to output
	PORTB |= (1<<2)|(1<<5);		//set pb2 to high
	DDRC &= (0<<2);		//set ddrc to input
	PORTC |= (0<<2);		//set portc2 to low
	TCCR0B |= (1<<CS00)|(1<<CS02);	// Set pre-scaler to 1024 
	
	//set local variables
	int ovFlowCount = 0;
	int ovCheck = 0;
	int delayCount = 77;		//amount of overflows to reach desired delay
	
	while (1) {
		if (!(PINC & (1 << PINC2))) //check for button press
		{
			PORTB &= ~(1<<2);		//if pressed then turn on led
			TCNT0 = 0;				//start counter at 0
			while(ovFlowCount <= delayCount ){
				ovCheck = TIFR0 & 0x01;	//variable to check if overflow met.
				if (ovCheck == 1){
					ovFlowCount ++;		//increase overflow count
					TIFR0 |= (1<<TOV0); //reset sreg flag
				}
			}
			ovFlowCount = 0;		//reset overflow count
		}
		else {
			PORTB |= (1<<2);		//if not pressed then keep led off
		}
	}
	return 0;
}

