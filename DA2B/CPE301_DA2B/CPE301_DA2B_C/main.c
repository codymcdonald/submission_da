/*
 * CPE301_DA2B_C.c
 *
 * Created: 3/2/2019 12:04:23 AM
 * Author : Cody
 */ 

#define F_CPU 16000000UL //set clock speed to 16MHz

//include important header files
#include <avr/io.h>		 
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void){
	//initialize registers	
   DDRB |= (1<<2)|(1<<5);
   PORTB |= (1<<5);	//set portb 2 to output
   PORTB |= (1<<2);		//set pb2 to high
   DDRC &= (0<<1)|(0<<2)|(0<<3);		//set ddrc to input 
   PORTC |= (1<<1)|(1<<2)|(1<<3);		//set portc2 to low
  
  // Enable PC at pins 9/10/11
  PCMSK1 |= (1<<PCINT9)|(1<<PCINT10)|(1<<PCINT11);
  PCICR |= (1<<PCIE1);
  sei();
  
while (1) ;

}


ISR (PCINT1_vect){
	PORTB ^= (1<<2);
	_delay_ms(1250);
}



