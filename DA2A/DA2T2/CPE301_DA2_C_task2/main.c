/*
 * CPE301_DA2_C_task2.c
 *
 * Created: 3/2/2019 12:04:23 AM
 * Author : Cody
 */ 

#define F_CPU 16000000UL //set clock speed to 16MHz

//include important header files
#include <avr/io.h>		 
#include <stdio.h>
#include <util/delay.h>


int main(void){
	//initialize registers	
   DDRB |= (1<<2);		//set portb 2 to output
   PORTB |= (1<<2);		//set pb2 to high
   DDRC &= (0<<2);		//set ddrc to input 
   PORTC |= (0<<2);		//set portc2 to low
    
	while (1) {
		if (!(PINC & (1 << PINC2))) //check for button press
		{
			PORTB &= ~(1<<2);		//if pressed then turn on led
			_delay_ms(1250);		//keep led on for 1.25s
		}
		else {
			PORTB |= (1<<2);		//if not pressed then keep led off
		}	
    }
return 0;	
}


