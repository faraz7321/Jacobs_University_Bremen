/*
 * lab4.c
 *
 * Created: 12-Sep-23 1:31:57 AM
 * Author : faraz
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>

void init_timer()
{
	// Set up timer with prescaler = 1024
	TCCR0B |= (1 << CS02) | (1 << CS00);

	// Initialize counter
	TCNT0 = 0;

	// Enable overflow interrupt
	TIMSK0 |= (1 << TOIE0);

	// Enable global interrupts
	sei();
}

/* Timer0 overflow interrupt service routine
 for Timer0 overflow. It counts 16 overflows to
 approximate a 1-second interval and toggles the LED
 */
ISR(TIMER0_OVF_vect)
{
	/*
	Assuming a clock frequency of 16MHz and a prescaler of 1024,
	the timer will overflow approximately every 32ms.
	To blink the LED every second, we need to count 32 overflows (approximately).
	*/
	static uint8_t overflow_count = 0;
	overflow_count++;
	if (overflow_count >= 32)
	{
		PORTD ^= (1 << PD3); // Toggle LED on PD3
		overflow_count = 0;
	}
}

int main(void)
{
	// Initialize PORTD3 as output
	DDRD |= (1 << PD3);

	// Initialize timer
	init_timer();

	while (1)
	{
		// Do nothing, interrupt will handle the toggling
	}

	return 0;
}
