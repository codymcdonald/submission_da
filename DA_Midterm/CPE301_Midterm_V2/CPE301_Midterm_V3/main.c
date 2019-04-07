/*
 * CPE301_Midterm_V3.c
 *
 * Created: 4/6/2019 4:12:34 PM
 * Author : Cody
 */ 

#define F_CPU 16000000UL

//Include Header Files
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h> 
#include <stdlib.h>

// Global constants for uart			
#define BAUD 115200
#define FOSC 16000000	
#define UBRR FOSC/8/BAUD-1

// Global variables
volatile uint8_t ADCdata;
volatile unsigned char temp[10];

//AT COMMAND STRINGS
volatile unsigned char AT[] = "AT\r\n"; // Test
volatile unsigned char CWMODE[] = "AT+CWMODE=3\r\n"; // Set Wi-Fi mode
volatile unsigned char CWJAP[] = "AT+CWJAP=\"Monarchs Palace\",\"quackquack\"\r\n"; // Get Wi-Fi info
volatile unsigned char CIPSTART[] = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"; // Establish connection with ThingSpeak
volatile unsigned char CIPSEND[] = "AT+CIPSEND=50\r\n"; // Send Temperature
volatile unsigned char CIPMUX[] = "AT+CIPMUX=0\r\n"; // Enable connection
volatile unsigned char SEND_DATA[] = "GET /update?key=ZDG1BP942G9NVEWD&field1="; // Get Write Key
volatile unsigned char RESET[] = "AT+RST\r\n"; // Get AT Firmware info
volatile unsigned char LINEBREAK[] = "\r\n"; // end of temperature transmission
volatile unsigned char CLOSE[] = "AT+CIPCLOSE\r\n";

//initialize functions
void ADC_init();
void usart_init();
void usart_send(volatile unsigned char data[]);


int main(void)
{
	// initialize modes
	ADC_init();		//initialize ADC
	usart_init();	//initialize usart
	sei();
	
	// Establish initial connection the thingspeak
	_delay_ms(1000);
	usart_send(RESET);		//reset ESP
	_delay_ms(1000);
	usart_send(AT);			//confirm communication
	_delay_ms(1000);
	usart_send(CWMODE);		//WiFi mode = 3
	_delay_ms(1000);
	usart_send(CWJAP);		//Send wifi login
	_delay_ms(1000);
	usart_send(CIPMUX);		//Single connection point
	
	while (1)
	{
		_delay_ms(1000);
		usart_send(CIPSTART);	// Connect to ThingSpeak
		_delay_ms(1000);
		usart_send(CIPSEND);	// Declare send length 50
		_delay_ms(1000);
		usart_send(SEND_DATA);	// Connect to proper key
		usart_send(temp);		// Send adc data
		usart_send(CLOSE);		// close connection
		usart_send(LINEBREAK);	// line break
	}
	return 0;
}

void ADC_init(){
	ADMUX |= (1 << REFS0); // use AVcc 
	ADMUX |= (1 << ADLAR); // Right adjust
	
	ADCSRA = (1 << ADEN)	// Enable  
	|(1 << ADPS1)	
	|(1 << ADPS0)	// 128 prescaler for 16Mhz
	|(1 << ADATE)	// ADC Auto Trigger
	|(1 << ADIE)	// Enable Interrupts
	|(1 << ADSC);	// Start ADC	
}

void usart_init() {
	UBRR0H = ((UBRR) >> 8);
	UBRR0L = UBRR;
	UCSR0A |= (1<< U2X0); // divisor baud = 8
	UCSR0B |= (1 << TXEN0); // Enable transmition
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bits
}
// ADC value Interrupt subroutine
ISR(ADC_vect) {
	unsigned char i;
	char dummy[10];
	
	ADCdata = (ADCH << 1) * 1.8 + 32; // Convert Celsius to Fahrenheit
	itoa(ADCdata, dummy, 10); //convert char to ascii
		for(i = 0 ; i < 10 ; i++){
		temp[i] = dummy[i]; //move converted ascii
	}
}

void usart_send(volatile unsigned char data[]) {
	volatile unsigned char length = 0;
	volatile unsigned char j;
	
	// write char array to UART register
	while(data[length] != 0){
		length++; 
		for(j = 0 ; j < length ; j++)
		{
			while(!(UCSR0A & (1<<UDRE0)));	// UART
			UDR0 = data[j];					// send char
		}
	}
}
