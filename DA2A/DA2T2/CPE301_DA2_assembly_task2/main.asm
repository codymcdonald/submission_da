;
; CPE301_DA2_assembly_task2.asm
;
; Created: 3/2/2019 3:31:09 PM
; Author : Cody
; TASK2

;TCNT for 1.25s = 0x4C4A

.ORG 0x00			;start memory at 0x00
LDI R20,5			;set clock prescaler to 1024 and normal mode
STS TCCR1B,R20		;attach value to correct register

CBI DDRC, 2			;set pin 2 to an input

LDI	R16,0b00111100	;set led pins to outputs
OUT DDRB, R16		;attach to ddr

LDI R16, 0xFF		;make sure all leds are off
OUT PORTB, R16


AGAIN: 
LDI R16, 0b00111100		;turn led's off 
OUT PORTB, R16			;output to port b
SBIC PINC,2				;skip next line if switch 2 is pressed
RJMP OVER				;jump to over subroutine
LDI R16, 0b00111000		;turn on led 
OUT PORTB, R16			;output to port

LDI R20,0x00			;reset the counter to 0
STS TCNT1H,R20
STS TCNT1L,R20
RCALL DELAY				;go to delay subroutine
RJMP AGAIN

OVER:					;subroutine to loop if button isn't pressed
SBI PORTB,2
RJMP AGAIN

DELAY:
 LDS R29, TCNT1H		;loading upper bit of counter to R29
 LDS R28, TCNT1L		;loading lower bit of counter to R28
 CPI R28,0x4A			;comparing if lower 8 bits of timer is 0x4A
 BRSH BODY				;if lower bits of timer have reached desired amount, check the upperbits
 RJMP DELAY				;otherwise, keep checking lower bits
BODY:
 CPI R29,0x4C			;check to see if upper timer bits have reached the desired value
 BRLT DELAY				;if not, recheck the lower bits
 RET					;once the timer reached the desired value, toggle the LED



