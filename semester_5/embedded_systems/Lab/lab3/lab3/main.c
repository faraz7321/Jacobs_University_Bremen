/*
 * lab3.c
 *
 * Created: 12-Sep-23 12:13:48 AM
 * Author : faraz
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

// Initialize the PORTD for LED output
void init_port()
{
    DDRD = 0xFF;          // Set all pins of PORTD as output
    PORTD &= ~(1 << PD2); // Set PD2 as low (for interrupt)
}

// Function to blink 3 LEDs connected to PORTD one after another
void blink_leds()
{
    PORTD = 0b00001000; // Turn on first LED at PD3
    _delay_ms(500);     // Wait for 500ms
    PORTD = 0b00010000; // Turn on second LED at PD4
    _delay_ms(500);     // Wait for 500ms
    PORTD = 0b00100000; // Turn on third LED at PD5
    _delay_ms(500);     // Wait for 500ms
}

// Function to blink all 3 LEDs three times simultaneously
void blink_all_three_times()
{
    for (int i = 0; i < 3; i++)
    {
        PORTD = 0b00111000; // Turn on all 3 LEDs at PD3, PD4, and PD5
        _delay_ms(500);     // Wait for 500ms
        PORTD = 0b00000000; // Turn off all LEDs
        _delay_ms(500);     // Wait for 500ms
    }
}

// External interrupt service routine
ISR(INT0_vect)
{
    blink_all_three_times();
}

int main(void)
{
    init_port(); // Initialize the PORTD

    // External interrupt settings
    EICRA |= (1 << ISC01); // Falling edge generates an interrupt request
    EIMSK |= (1 << INT0);  // Enable external interrupt INT0

    sei(); // Enable global interrupts

    while (1)
    {
        blink_leds(); // Blink LEDs one after another
    }

    return 0;
}
