;
; CPE310_DA1B.asm
;
; Created: 2/22/2019 3:05:56 PM
; Author : Cody
;
.CSEG
.ORG 0X00

;Initialize all constants
.EQU COUNT = 99
.EQU STARTADDS	= 0x200		;address for all numbers being filled in
.EQU DIVISIBLE	= 0x400		;address for all divisble numbers
.EQU NOTDIV		= 0x600		;address for all non divisible numbers

;Set all high and low bits for the address registers
LDI XL, LOW(STARTADDS)
LDI XH, HIGH(STARTADDS)
LDI	YL, LOW(DIVISIBLE)
LDI YH, HIGH(DIVISIBLE)
LDI ZL, LOW(NOTDIV)
LDI ZH, HIGH(NOTDIV)

;set dummy and count registers
LDI R23, COUNT
LDI R20, 0

;ADD HIGH AND LOW
MOV R20, XL
ADD R20, XH

;cycle through the numbers that need to be sorted
INCREMENT1:
INC R20
CPI R20, 11
BREQ STORENUM
RJMP INCREMENT1

INCREMENT2:
INC R20

;store each number into x register and increment the value
STORENUM:
ST X+,R20
DEC R23
BRNE INCREMENT2

;PROBLEM 2: PARSE THROUGH CODE
LDI XL, LOW(STARTADDS) ;start at initial address
LDI XH, HIGH(STARTADDS)

;start loop for parsing
DIV3:
LD R22, X+
MOV R24, R22
CPI R22, 0
BREQ PROB3

;check if it's divisble
DIVIDE:
SUBI R22,3
BREQ divisible_store
BRMI negative_store
RJMP DIVIDE

;store value into y register if divisbile
divisible_store:
ST Y+,R24
RJMP DIV3

;store into z if the number is not divisible by 3
negative_store:
ST Z+,R24
RJMP DIV3

;Problem 3
;Initialize the pointers to initial addresses
PROB3:
LDI	YL, LOW(DIVISIBLE)
LDI YH, HIGH(DIVISIBLE)
LDI ZL, LOW(NOTDIV)
LDI ZH, HIGH(NOTDIV)

;Sum all Y pointer values
SUMY:
LDI R20,0		;dummy register
LD R21,Y+		;check when Y is empty register
ADD R16, R21	;add each value into R18
ADC R17, R20	;add each carry into R19
CPI R21,0		;Compare R21 with 0
BREQ SUMZ		;Stop loop when 0 value is found and go to sumz
RJMP SUMY	    ;jump back to sumz if 0 condition isn't satisfied

SUMZ:
LDI R20,0		;dummy register
LD R21,Z+		;check when Z is empty register
ADD R18, R21	;add each value into R18
ADC R19, R20	;add each carry into R19
CPI R21,0		;Compare R21 with 0
BREQ end		;Stop loop when 0 value is found
RJMP SUMZ		;jump back to sumz if 0 condition isn't satisfied


 end: rjmp end





