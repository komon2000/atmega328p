#include <avr/io.h>
#include <util/delay.h>

#define LED PB5     // Arduino Uno built-in LED on pin 13

int main(void)
{
    DDRB |= (1 << LED);     // make the LED pin an OUTPUT

    while(1)
    {
        PORTB |= (1 << LED);    // LED ON
        _delay_ms(500);

        PORTB &= ~(1 << LED);   // LED OFF
        _delay_ms(500);
    }
}
