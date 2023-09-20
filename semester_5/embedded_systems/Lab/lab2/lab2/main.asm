	;
	; lab2.asm
	;
	; Created: 11 - Sep - 23 8:15:42 PM
	; Author : faraz
	;
	
	; Replace with your application code
	.org 0x0000
	rjmp main

	.org INT0addr
	rjmp INT0_handler

	.org INT_VECTORS_SIZE
	.def dreg = r18

main:
	cli
	ldi r17, LOW(RAMEND)
	out SPL, r17
	ldi r17, HIGH(RAMEND)
	out SPH, r17                 ; set Stack Pointer
	sbi DDRB, 0x00               ; set PB0 as output (Pin 8)
	sbi PORTB, 0x00              ; set PB0
	cbi DDRD, 0x02               ; set PD2 as input
	cbi PORTD, 0x02
	ldi r16, 0x01                ; enable external interrupts
	out EIMSK, r16
	ldi r16, 0x05                ; change triggers
	sts EICRA, r16
	ldi r16, 0x20
	sei

loop:
	rjmp loop

INT0_handler:
	push r17
	in r17, SREG                 ; push status register to SP
	com r16
	out PORTB, r16               ; negate PORTB (PINB5)
	out SREG, r17                ; restore status register
	pop r17
	reti                         ; return from handler (INT0)
