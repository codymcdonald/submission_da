/*
 * CPE301_DA4A_V2.c
 *
 * Created: 4/13/2019 2:29:12 PM
 * Author : Cody
 */ 

//include header file
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Global variables
volatile unsigned int ADC_Val;			// holds value of ADC
int flag = 0;							// used to toggle

int main(void){
	//Set DDR's
	DDRB |= (1<<PB1)|(1<<PB5);		//PB1 and PB5 as outputs PB5 is the first LED
	DDRC = 0;						//PORTC as input	
	PORTB = 0;						//reset portb to low
	PORTC |= (1<<PC1);				//set PC1 high
	
	// Initialize Timer 1
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);	// Fast PWM, Non-inverted mode
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11);		// Pre-scaler set to 8
	ICR1 = 9999;									// Top of timer1 set to 9999
	
	// Set interrupts
	PCICR = (1<<PCIE1);		//Enable PCINT
	PCMSK1 = (1<<PCINT9);   //Set interrupt for PC1
	
	//Set up ADC
												
	ADMUX = (1<<REFS0);												// PC0 is input for ADC
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);		// enable ADC, system clock used for ADC
	ADCSRB = 0x0;													// free running mode
	DIDR0 = 0x1;													// Filter out any digital signals	
	
	sei();			//Enable interrupts
	
	while (1);		//infinite loop
}


//ISR for PC1
ISR(PCINT1_vect){
	_delay_ms(500);	//Debounce delay. Button needs to be held to toggle
	if(!(PINC & (1 << PINC1))){
		while(!(PINC & (1 << PINC1))){
			if(flag == 1){
				PORTB |= (1 << PORTB1) | (1 << PORTB5); //turn on OC1A and LED off
				ADCSRA |= (1 << ADSC);				// start conversion
				while((ADCSRA&(1<<ADIF))==0){		// wait for conversion to finish
					ADC_Val = ADC & 0x03FF;			// we only need first 10 bits
					OCR1A = 10*ADC_Val;				// Calculate duty cycle
				}				
			}
			else if(flag == 0){
				OCR1A = 0;					//reset 
				PORTB &= ~(1 << PORTB1);	
				PORTB &= ~(1 << PORTB5);	//turn off OC1A and LED on
			}
		}
		flag ^= 1;			//toggle	
	}
}


