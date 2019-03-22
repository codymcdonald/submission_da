/*
 * CPE301_DA2C_task1.c
 *
 * Created: 3/19/2019 11:30:40 PM
 * Author : Cody
 */ 

#include <stdio.h>
#include <avr/io.h>

//0.725s period
//60% = 0.435s. TCNT = 6796 = 1A8C
//40% = 0.29s. TCNT = 4530 = 11B2

int main(void)
{
	DDRB |= (1<<2)|(1<<5);		// led 2 and 5 to output
	PORTB |= (1<<5);
	TCCR0B |= (1<<CS00)|(1<<CS02);	// Set pre-scaler to 1024 
	
	//declare vital variables
	int ovFlowCount = 0;
	int ovCheck = 0;
	int flag = 1;
	int dc60 = 27; //overflow count to reach 6796
	int dc40 = 18; //overflow count to reach 4530

	TCNT0 = 0; //initialize clock
	// Run loop for 60% DC
	while(1){
		ovCheck = TIFR0 & 0x01;	//variable to check if overflow met.
		
		if(ovCheck == 1){
			ovFlowCount ++;
			TIFR0 |= (1<<TOV0); //reset overflow flag
		}
		
		if (flag == 0 && ovFlowCount == dc40){
			PORTB &= ~(1<<2); //turn on LED
			TCNT0 = 0;		//reset counter
			ovFlowCount = 0; //reset ov counter
			flag = 1;
		}
		else if(flag == 1 && ovFlowCount == dc60){
			PORTB |= (1<<2); // turn off LED
			TCNT0 = 0;		//reset counter
			ovFlowCount = 0; //reset ov counter
			flag = 0;
		}
	}
	return 0;
}

