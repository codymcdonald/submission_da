;
; CPE301_A1.asm
;
; Created: 2/7/2019 1:18:10 PM
; Author : Cody McDonald

.include<m328pdef.inc>

.cseg
.org 0x00

.EQU MULTIPLICAND = 0xFFFF			;Set a value to the multiplicand
.EQU MULTIPLIER = 0xFF			;Set value for the multiplier
.EQU ZERO = 0x0000					;Set universal zero value

  LDI	R25, HIGH(MULTIPLICAND)		;load R25 with higher bit Multiplicand
  LDI	R24, LOW(MULTIPLICAND)		;load R24 with lower Multiplicand
  LDI	R22, MULTIPLIER				;Multiplier value will remain same
  LDI	R16, MULTIPLIER				;This register's value will keep changing
  LDI	R17, ZERO
  
  ;Set up MUL test  
  LDI	R28, 0X25
  MUL	R28, R22

  L1:
  ADD	R18, R24		;Add value of register 24 to 18
  ADC	R19, R25		;Add value of register 25 to 19 plus any carry
  ADC	R20, R17		;Add any remaining carry to register 20
 
  DEC	R16				;Decrease the index

  BRNE	L1				;Loop back to L1 until index is zero
  
  ;End program sequence
  jmp end
  end: rjmp end 







