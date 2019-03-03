; CPE301_DA2_assembly.asm
;
; Author : Cody 
; TASK1

;0.725s period
;60% = 0.435s. TCNT = 6796 = 1A8C
;40% = 0.29s. TCNT = 4530 = 11B2

.org 0
LDI R16, 0b00111100		;representing PB
OUT DDRB, R16			;enable PB as output
LDI R20,5				;set clock prescaler to 1024
STS TCCR1B,R20

begin:
LDI R20,0x00		;resetting the counter to 0
STS TCNT1H,R20
STS TCNT1L,R20
RCALL delay			;calling timer to wait for 1 sec
LDI R17,0b00111100	;XOR to toggle led
OUT PORTB,R17		;output to port b

;RUN SEQUENCE FOR LED OFF
LDI R20,0x00		;resetting the counter to 0
STS TCNT1H,R20
STS TCNT1L,R20
RCALL delay2		;calling timer to wait for 1 sec
LDI R17,0b00111000	;XOR to toggle led
OUT PORTB,R17
RJMP begin			;repeat main loop

delay:
 LDS R29, TCNT1H	;loading upper bit of counter to R29
 LDS R28, TCNT1L	;loading lower bit of counter to R28
 CPI R28,0x8C		;comparing if lower 8 bits of timer is 0x8C
 BRSH body			;if lower bits of timer have reached desired amount, check the upperbits
 RJMP delay			;otherwise, keep checking lower bits
body:
 CPI R29,0x1A		;check to see if upper timer bits have reached the desired value
 BRLT delay			;if not, recheck the lower bits
 RET				;once the timer reached the desired value, toggle the LED
delay2:
 LDS R29, TCNT1H	;loading upper bit of counter to R29
 LDS R28, TCNT1L	;loading lower bit of counter to R28
 CPI R28,0xB2		;comparing if lower 8 bits of timer is 0xB2
 BRSH body2			;if lower bits of timer have reached desired amount, check the upperbits
 RJMP delay2		;otherwise, keep checking lower bits
body2:
 CPI R29,0x11		;check to see if upper timer bits have reached the desired value
 BRLT delay2		;if not, recheck the lower bits
 RET				;once the timer reached the desired value, toggle the LED