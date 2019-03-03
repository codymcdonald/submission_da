/*
 * CPE301_DA2_C_task1.c
 *
 * Author : Cody
 */ 


#include <stdio.h>
#include <avr/io.h>

//0.725s period
//60% = 0.435s. TCNT = 6796 = 1A8C
//40% = 0.29s. TCNT = 4530 = 11B2

int main(void)
{
	DDRB |= (1<<2);		// Set all PORTB out
	TCCR1B = 0x0D;		// Set pre-scaler to 1024 and CTC Mode
	OCR1A = 0x1A8C;		// Set top of OCR1A to 0.435s
	int flag = 0;       // set flag variables
	int flag2 = 1;

	// Run loop for 60% DC
	while(1){
		flag = TIFR1 & 0x04;
		if (flag == 0x04 && flag2 == 0){
			PORTB &= ~(1<<2); //turn off LED
			TIFR1 = 0x04;	  //reset clear flag
			OCR1A = 0x11B2;   //set delay for LED off
			flag2 = 1;
		}
		else if(flag== 0x04 && flag2 == 1){
			PORTB |= (1<<2); // turn on LED
			TIFR1 = 0x04;	 // reset clear flag
			OCR1A = 0x1A8C;  // set delay for LED on
			flag2 = 0;
		}
	}
	return 0;
}

