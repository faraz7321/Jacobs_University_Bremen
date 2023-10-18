/*
 * lab8.c
 *
 * Created: 16-Oct-23 1:08:21 PM
 * Author : faraz
 * Hardware PWM is used for pins D5 and D6, which are connected to Timer0.
 * Software PWM is implemented for pin D7 using Timer1 and its Compare Match A interrupt.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

volatile uint8_t pwmValue = 0; // For software PWM on D7

void ADC_init()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
}

void PWM_init()
{
	// For D5 (Timer0, Channel B)
	TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B = (1 << CS00);
	DDRD |= (1 << PD5);

	// For D6 (Timer0, Channel A)
	TCCR0A |= (1 << COM0A1);
	DDRD |= (1 << PD6);

	// Software PWM for D7
	DDRD |= (1 << PD7);

	// Timer1 for software PWM
	TCCR1B = (1 << WGM12) | (1 << CS11);
	TIMSK1 = (1 << OCIE1A);
	OCR1A = F_CPU / 8 / 490; // Approx 490 Hz
}

ISR(ADC_vect)
{
	uint16_t adcValue = ADC;
	pwmValue = (adcValue >> 2) & 0xFF; // For software PWM on D7

	OCR0A = pwmValue; // D6
	OCR0B = pwmValue; // D5

	ADCSRA |= (1 << ADSC);
}

ISR(TIMER1_COMPA_vect)
{
	static uint8_t counter = 0;
	counter++;
	if(counter < pwmValue)
	PORTD |= (1 << PD7);
	else
	PORTD &= ~(1 << PD7);

	if(counter == 255)
	counter = 0;
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
Connect the middle pin of the potentiometer to ADC0 (pin PC0 or Arduino analog pin A0).
Connect one of the other pins of the potentiometer to 5V and the other to GND.

Connect the longer leg of LED1 to pin PD7 (Arduino pin D7)
Connect the longer leg of LED2 to pin PD5 (Arduino pin D5)
Connect the longer leg of LED3 to pin PD6 (Arduino pin D6)

Connect the shorter legs of the LEDs to GND.
*/
