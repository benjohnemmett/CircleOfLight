#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define PIN_OUT PB0

int main() {
    SetupUart();
    EnableUartTransmission();

    DDRB |= (1 << PIN_OUT);

    while (1) {
        PORTB |= (1 << PIN_OUT);
        _delay_ms(200);
        PORTB &= ~(1 << PIN_OUT);
        _delay_ms(300);

        SendByteToUart('v');
    }
}
