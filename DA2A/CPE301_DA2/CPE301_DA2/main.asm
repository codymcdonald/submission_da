;
; CPE301_DA2.asm
;
; Created: 3/1/2019 3:58:47 PM
; Author : Cody
;

;0.725s period
;60% = 0.435s. TCNT = 6796 = 1A8C
;40% = 0.29s. TCNT = 4530 = 11B2

;Square wave with a period of 2 seconds
.org 0x00

.MACRO TIMERSET
;Reset TOP of counter for LED off time
LDI R21,@0		;Load higher value to OCR1A
LDI R20,@1		;Load lower value to OCR1A
STS OCR1AH, R21
STS OCR1AL, R20
.ENDMACRO

;Initialize vital registers
LDI R20, 0b00111100		;Set DDRB as output 
LDI R16, 0b00000100		;Set LED D4 on
OUT DDRB, R20			;Set DDRB as output
LDI R17, 0b00111100		;used to set or reset PB5
LDI R20,0x0D			;set to ctc mode
STS TCCR1B,R20			;Set to ctc mode
LDI R21, 0x04			;Set reset value for OCF1A
LDI R23, 0				;flag we will use to determine which duty cycle to use

;Set Initial Time
TIMERSET 0x1A,0x8C

begin:
NOP
NOP
RCALL delay			;calling timer to wait for 1 sec
EOR R17,R16			;XOR to toggle led
OUT PORTB,R17
RCALL LEDCHECK
RJMP begin			;repeat main loop

delay:
IN R28,TIFR1		;loading lower bit of counter to R28
ANDI R28,0x04
CPI R28,0x04		;comparing if lower 8 bits of timer is 0x08
BREQ BODY		;after delay, check if we need to set LED delay to 60% or 40%
RJMP delay			;otherwise, continue checking for flag

BODY:
OUT TIFR1, R21		;Reset timer flag
RET

LEDCHECK:
CPI R23, 1
BREQ LEDOFF
TIMERSET 0xF1,0xB2
LDI R23, 1
RET

LEDOFF:
TIMERSET 0xFA,0x8C
LDI R23, 0
RET


;end: rjmp end
