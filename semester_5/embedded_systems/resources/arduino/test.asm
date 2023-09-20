;
; Lab2.asm
;
; Created: 11-Sep-23 1:45:14 PM
; Author : faraz
;

;code
.include "m328def.inc"
 
.org 0x0000
        RJMP begin; jump to begin  
        .org 0x0001
        RJMP interupt ;
.org 0x0034 
begin: CLI
        LDI    R16,low(RAMEND)
        OUT    SPL,R16
        LDI    R16,high(RAMEND)
        OUT    SPH, R16                
        LDI    R16,0xFF 
        OUT    DDRD, R16   
        LDI    R16,0xFF 
        OUT    PORTD, R16
        RCALL  Delay
        LDI    R16,0x00
		 
        OUT     PORTD, R16
        RCALL   Delay
Delay:  LDI     R17, 0xFF
	    LDI     R18, 0xFF
		LDI     R19, 0xFF
loop:   DEC     R17 
		BRNE    loop  

loop2:	LDI R17, 0xFF
		DEC R18
		BRNE loop	   

loop3:	LDI R18, 0x1F
		DEC R19
		BRNE loop	  
		RET
		sei  