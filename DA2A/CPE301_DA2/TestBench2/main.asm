
;Lab 3

;Square wave with a period of 2 seconds
.org 0
LDI R16,0x04	;Make all pins an output
OUT DDRB, R16	;enable Port B as output
LDI R17,0		;used to set or reset PB5
LDI R20,0x0D	;set to ctc mode
STS TCCR1B,R20	

LDI R20,0x04 ;Load lower value to OCR1A
LDI R21,0x0F  ;Load higher value to OCR1A
STS OCR1AH, R21
STS OCR1AL, R20


LDI R21, 0x04 ;Set rest value for OCF1A

begin:
RCALL delay ;calling timer to wait for 1 sec
EOR R17,R16 ;XOR to toggle led
OUT PORTB,R17
RJMP begin ;repeat main loop

delay:
 IN R28,TIFR1 ;loading lower bit of counter to R28
 ANDI R28,0x04
 CPI R28,0x04 ;comparing if lower 8 bits of timer is 0x08
 BREQ body ;if lower bits of timer have reached desired amount
 RJMP delay ;otherwise, continue checking for flag

body:
OUT TIFR1, R21 ;reset TIFR1
RET


