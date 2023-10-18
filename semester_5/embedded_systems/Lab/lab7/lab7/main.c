/*
 * lab7.c
 *
 * Created: 16-Oct-23 1:29:09 PM
 * Author : faraz
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>

void ADC_init()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
}

void PWM_init()
{
	// For D6 (Timer0, Channel A)
	TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B = (1 << CS00);
	DDRD |= (1 << PD6);
}

ISR(ADC_vect)
{
	uint16_t adcValue = ADC;
	uint8_t pwmValue = (adcValue >> 2) & 0xFF;

	OCR0A = pwmValue; // PWM width for D6

	ADCSRA |= (1 << ADSC);
}

int main(void)
{
	ADC_init();
	PWM_init();

	sei(); // Enable global interrupts

	ADCSRA |= (1 << ADSC); // Start ADC conversion

	while (1)
	{
		// Main loop
	}

	return 0;
}

/*
Wiring:
Connect the middle pin of the potentiometer to ADC0 (which is pin PC0 or Arduino analog pin A0).
Connect one of the other pins of the potentiometer to 5V and the other to GND.
Connect the longer leg of the LED to pin PD6 (Arduino pin D6)
Connect the shorter leg of the LED to GND
*/


