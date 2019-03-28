/*
 * CPE301_DA3A.c
 *
 * Created: 3/27/2019 7:10:08 PM
 * Author : Cody McDonald
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void USART_tx_data(char data);			// Function to send integer/char
void USART_tx_string(char* StringPtr);	// Function to send string 
void USART_init(void);					// Function to initialize the UART communication

char str_type[] = "String: ";		// Declaring the string value on screen
char int_type[] = "Integer: ";		// Declaring the integer value on screen
char float_type[] = "Floating Point: "; // Declaring the floating point value on screen
char line[] = "\n";					// Used to create the next line
char string[] = "I love eggs";		//String[] is the variable to output into terminal
char output[20];					// Allocating memory space to contain the float value
volatile float adc_temp = 100.00;	// Sets the float value

int main(void)
{
	TCCR1B |= 5;		// Sets prescaler to 1024
	TIMSK1 = (1 << TOIE1); // Enables overflow flag
	TCNT1 = 49911;		// Set top of timer for a delay of 1 second
	USART_init();		// Initializes the analog to digital functions as well as OVF interrupt
	sei();				//enable interrupts
	
	while(1);			//infinite loop
}

ISR (TIMER1_OVF_vect)
{
	USART_tx_string(line);			// go to next line
	USART_tx_string(str_type);		// Label the string
	USART_tx_string(string);		// prints string 
	USART_tx_string(line);			// creates next line
	USART_tx_string(int_type);		// Label the integer
	USART_tx_data('8');				// prints value a numerical value
	USART_tx_string(line);			// creates next line
	USART_tx_string(float_type);	// Label the FLoating Point
	snprintf(output, sizeof(output), "%f\r\n", adc_temp); // output everything
	USART_tx_string(output);		// transmits outs to UART
	USART_tx_string(line);			// creates next line
	TCNT1 = 49911;					// reset top of counter
}


//Function to initialize UART
void USART_init( void )
{
	UBRR0H = 0;
	UBRR0L = F_CPU/16/BAUD - 1; // Used for the BAUD prescaler
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}


//create function to send character data
void USART_tx_data(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));	// Set proper modes for UARRT
		UDR0 = data;					// grabs the value given from data
	
}

//create function to send strings
void USART_tx_string(char *StrPtr)
{
	while ((*StrPtr != '\0')){				// loop until end of line
		while (!(UCSR0A & (1 << UDRE0)));	// loop until UDRE0 is high
			UDR0 = *StrPtr;					// Store value intp UDR0
				StrPtr++;					// increase to next position
	}
}
