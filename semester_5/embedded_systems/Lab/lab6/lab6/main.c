/*
 * lab6.c
 *
 * Created: 25-Sep-23 12:32:38 PM
 * Author : faraz
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init()
{
	// Set reference voltage to AVCC
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
}

void PWM_init()
{
	TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
	TCCR1B = (1 << CS10);
	DDRB |= (1 << PB1); // PB1 as output (Arduino Pin-9 )
}

ISR(ADC_vect)
{
	uint16_t adcValue = ADC;
	uint8_t pwmValue = (adcValue >> 2) & 0xFF;

	OCR1A = pwmValue; // PWM width

	ADCSRA |= (1 << ADSC);
}

int main(void)
{
	ADC_init();
	PWM_init();

	// Enable global interrupts
	sei();

	ADCSRA |= (1 << ADSC);

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
Connect the longer leg of the LED to pin PB1 (Arduino pin 9)
Connect the shorter leg of the LED to GND
*/
