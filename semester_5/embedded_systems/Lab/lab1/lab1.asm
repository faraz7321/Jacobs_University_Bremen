;lab1
;uses CALL/RCALL    
    
    .org 0x0000
    rjmp start  ; Jump to the start of the program

start:
    ldi r16, 0xFF   ; Load 0xFF into r16
    out 0x0A, r16   ; Set DDRD as output (all bits)

main_loop:
    in r16, 0x0B    ; Read the current state of PORTD
    com r16         ; Complement the bits
    out 0x0B, r16   ; Write the toggled state back to PORTD
    
    call delay_1s   ; Call the 1-second delay subroutine
    
    rjmp main_loop  ; Repeat the loop

; Delay subroutine (assuming 16 MHz clock)
delay_1s:
    ldi r18, 78     ; Outer loop counter (adjusted for 16 MHz)
outer_loop:
    ldi r19, 250   ; Inner loop counter
inner_loop:
    dec r19
    brne inner_loop
    dec r18
    brne outer_loop
    
    ret            ; Return to the caller
