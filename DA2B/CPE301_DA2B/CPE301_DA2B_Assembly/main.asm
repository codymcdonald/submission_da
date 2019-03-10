;
; CPE301_DA2B_assembly_task2.asm
;
; Author : Cody
; TASK2

.include <m328pdef.inc>

.ORG 0x00			;start memory at 0x00
JMP MAIN

.ORG 0X10			;jump memory back to 0x10
JMP PCINT1_ISR

MAIN:

	;Set stack pointers
	LDI R20, HIGH(RAMEND)
	OUT SPH, R20
	LDI R20, LOW(RAMEND) 
	OUT	SPL, R20

	;Initialize ports
	LDI R17, 0b0011_1000	;reset register
	LDI R19, 4				;used to toggle 4th LED
	LDI R21, 0xFF			;used to set DDRB high
	
	OUT DDRB, R21		;set led ports to high
	OUT	PORTB, R21		;set leds to low
	
	OUT	DDRC, R19		;set ddrc to inputs
	;Set modes for interrupt 
	LDI R20,0b0000_0100
	STS PCMSK1, R20
	OUT PORTC, R20 
	LDI R20, (1<<PCIE1)
	STS PCICR, R20
	SEI					;start interrupt

;Run an infinite loop
HERE:
OUT PORTB,R21 ;keep LED off unless 
 JMP HERE

;interrupt subroutine
PCINT1_ISR:
	EOR R17,R19
	OUT PORTB,R17

	;delay subroutine
    ldi  r22, 104
    ldi  r23, 118
    ldi  r24, 194
L1: dec  r24
    brne L1
    dec  r23
    brne L1
    dec  r22
    brne L1
	RETI	;return back to loop




