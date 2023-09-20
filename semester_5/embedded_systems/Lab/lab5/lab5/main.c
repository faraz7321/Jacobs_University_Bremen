/*
 * lab5.c
 *
 * Created: 19-Sep-23 9:23:14 AM
 * Author : faraz
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

// Initialize Timer1 in CTC mode
void setup_timer1_ctc_mode();

// Initialize Timer1 in PWM mode
void setup_timer1_pwm_mode();
void pwm_cycle();

//ISR(TIMER1_COMPA_vect)
//{
    //PORTD ^= 0xFF;
    //PORTB ^= (1 << PORTB1);
//}

int main(void)
{
    // setup_timer1_ctc_mode();
	void setup_timer1_pwm_mode();
	
    //sei();

    while (1)
    {
        pwm_cycle();
    }

    return 0;
}

void setup_timer1_ctc_mode()
{
	DDRD = 0xFF;         // PORTD as output
	DDRB |= (1 << DDB1); // OCR1A
    // Clear Timer1 control registers
    TCCR1A = 0;
    TCCR1B = 0;

    // OCR1A = (Clock Freq / (Prescaler x Target Freq) ) - 1
    // OCR1A = (16000000 / (256 x 1 )) -1 = 62499
    OCR1A = 62499;

    // Enable CTC mode
    TCCR1B |= (1 << WGM12);

    // Enable Output Compare Match interrupt mask
    TIMSK1 |= (1 << OCIE1A);

    // Set prescaler to 256
    TCCR1B |= (1 << CS12);
}

void setup_timer1_pwm_mode()
{
    DDRB |= (1 << DDB1);

    // Set Timer1 to Fast PWM mode with non-inverted output
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11); // Set prescaler to 8

    // Initialize OCR1A value (0 to 255 for 8-bit Fast PWM)
    OCR1A = 0;
}

void pwm_cycle()
{
    // Increase brightness
    for (uint16_t i = 0; i < 65535; i += 128) {
	    OCR1A = i;
	    _delay_ms(10);
    }

    // Decrease brightness
    for (uint16_t i = 65535; i > 0; i -= 128) {
	    OCR1A = i;
	    _delay_ms(10);
    }
}