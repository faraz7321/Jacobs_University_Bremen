	;
	; lab2.asm
	;
	; Created: 11 - Sep - 23 8:15:42 PM
	; Author : faraz
	;
	
	; Replace with your application code
	.include "m328pdef.inc"
	
	.cseg
	.org 0x00
	clr r17                      ; clear led register
	; Arduino PIN D8
	ldi r16, (1<<PINB0)          ; load 00000001 into r16 register
	out DDRB, r16                ; set PINB0 to output
	
	.equ inner_loop_val = 28168
	
start:                        ;start code
	eor r17, r16                 ; toggle PINB0 in led register
	out PORTB, r17               ; write led register to PORTB
	
	ldi r18, 71                  ; initialize outer loop count
	
	; Delay loops
outerLoop:
	ldi r24, LOW(inner_loop_val) ; intialize inner loop count in inner
	ldi r25, HIGH(inner_loop_val) ; loop high and low registers
	
innerLoop:
	sbiw r24, 1                  ; decrement inner loop registers
	brne innerLoop               ; branch to innerLoop if innerLoop registers != 0
	
	dec r18                      ; decrement outer loop register
	brne outerLoop               ; branch to outerLoop if outer loop register != 0
	
	rjmp start                   ; jump to start