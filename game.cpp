#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

#define LIGHT_01_PORT PORTB
#define LIGHT_02_PORT PORTB
#define LIGHT_03_PORT PORTB
#define LIGHT_04_PORT PORTB
#define LIGHT_05_PORT PORTC
#define LIGHT_06_PORT PORTC
#define LIGHT_07_PORT PORTC
#define LIGHT_08_PORT PORTC
#define LIGHT_09_PORT PORTD
#define LIGHT_10_PORT PORTD
#define LIGHT_11_PORT PORTD
#define LIGHT_12_PORT PORTB

#define LIGHT_01_DDR DDRB
#define LIGHT_02_DDR DDRB
#define LIGHT_03_DDR DDRB
#define LIGHT_04_DDR DDRB
#define LIGHT_05_DDR DDRC
#define LIGHT_06_DDR DDRC
#define LIGHT_07_DDR DDRC
#define LIGHT_08_DDR DDRC
#define LIGHT_09_DDR DDRD
#define LIGHT_10_DDR DDRD
#define LIGHT_11_DDR DDRD
#define LIGHT_12_DDR DDRB

#define LIGHT_01_PIN PB1
#define LIGHT_02_PIN PB2
#define LIGHT_03_PIN PB6
#define LIGHT_04_PIN PB7
#define LIGHT_05_PIN PC0
#define LIGHT_06_PIN PC1
#define LIGHT_07_PIN PC2
#define LIGHT_08_PIN PC3
#define LIGHT_09_PIN PD5
#define LIGHT_10_PIN PD6
#define LIGHT_11_PIN PD7
#define LIGHT_12_PIN PB0

#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN_REG PIND
#define PLAY_BTN_PIN PD4
#define MINUS_BTN_PIN PD3
#define PLUS_BTN_PIN PD2

volatile uint8_t activePin = 1;
uint8_t rotationIsClockWise = 0;
uint8_t currentCycle = 0;
uint8_t cyclesPerLight = 5;

typedef struct {
    uint8_t state;
    uint8_t transitionCounter;
    uint8_t isPressed;
} button_state_t;

button_state_t playButton = {0, 0, 0};
button_state_t plusButton = {0, 0, 0};
button_state_t minusButton = {0, 0, 0};

void SetOutputPins() {
    LIGHT_01_DDR |= _BV(LIGHT_01_PIN);
    LIGHT_02_DDR |= _BV(LIGHT_02_PIN);
    LIGHT_03_DDR |= _BV(LIGHT_03_PIN);
    LIGHT_04_DDR |= _BV(LIGHT_04_PIN);
    LIGHT_05_DDR |= _BV(LIGHT_05_PIN);
    LIGHT_06_DDR |= _BV(LIGHT_06_PIN);
    LIGHT_07_DDR |= _BV(LIGHT_07_PIN);
    LIGHT_08_DDR |= _BV(LIGHT_08_PIN);
    LIGHT_09_DDR |= _BV(LIGHT_09_PIN);
    LIGHT_10_DDR |= _BV(LIGHT_10_PIN);
    LIGHT_11_DDR |= _BV(LIGHT_11_PIN);
    LIGHT_12_DDR |= _BV(LIGHT_12_PIN);
}

void SetLightValue(uint8_t index, uint8_t value) {
    switch (index) {
        case 1:
            if (value) {LIGHT_01_PORT |= _BV(LIGHT_01_PIN);} else {LIGHT_01_PORT &= ~_BV(LIGHT_01_PIN);}
            break;
        case 2:
            if (value) {LIGHT_02_PORT |= _BV(LIGHT_02_PIN);} else {LIGHT_02_PORT &= ~_BV(LIGHT_02_PIN);}
            break;
        case 3:
            if (value) {LIGHT_03_PORT |= _BV(LIGHT_03_PIN);} else {LIGHT_03_PORT &= ~_BV(LIGHT_03_PIN);}
            break;
        case 4:
            if (value) {LIGHT_04_PORT |= _BV(LIGHT_04_PIN);} else {LIGHT_04_PORT &= ~_BV(LIGHT_04_PIN);}
            break;
        case 5:
            if (value) {LIGHT_05_PORT |= _BV(LIGHT_05_PIN);} else {LIGHT_05_PORT &= ~_BV(LIGHT_05_PIN);}
            break;
        case 6:
            if (value) {LIGHT_06_PORT |= _BV(LIGHT_06_PIN);} else {LIGHT_06_PORT &= ~_BV(LIGHT_06_PIN);}
            break;
        case 7:
            if (value) {LIGHT_07_PORT |= _BV(LIGHT_07_PIN);} else {LIGHT_07_PORT &= ~_BV(LIGHT_07_PIN);}
            break;
        case 8:
            if (value) {LIGHT_08_PORT |= _BV(LIGHT_08_PIN);} else {LIGHT_08_PORT &= ~_BV(LIGHT_08_PIN);}
            break;
        case 9:
            if (value) {LIGHT_09_PORT |= _BV(LIGHT_09_PIN);} else {LIGHT_09_PORT &= ~_BV(LIGHT_09_PIN);}
            break;
        case 10:
            if (value) {LIGHT_10_PORT |= _BV(LIGHT_10_PIN);} else {LIGHT_10_PORT &= ~_BV(LIGHT_10_PIN);}
            break;
        case 11:
            if (value) {LIGHT_11_PORT |= _BV(LIGHT_11_PIN);} else {LIGHT_11_PORT &= ~_BV(LIGHT_11_PIN);}
            break;
        case 12:
            if (value) {LIGHT_12_PORT |= _BV(LIGHT_12_PIN);} else {LIGHT_12_PORT &= ~_BV(LIGHT_12_PIN);}
            break;
    }
}

void SetupButtonPins() {
    BTN_DDR &= ~_BV(PLAY_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(PLAY_BTN_PIN); // Set internal pull up resister

    BTN_DDR &= ~_BV(PLUS_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(PLUS_BTN_PIN); // Set internal pull up resister

    BTN_DDR &= ~_BV(MINUS_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(MINUS_BTN_PIN); // Set internal pull up resister
}

void IncrementActiveLight() {
    activePin += 1;
    if (activePin > 12) {
        activePin = 1;
    }
}

void DecrementActiveLight() {
    if (activePin > 1) {
        activePin--;
    } else {
        activePin = 12;
    }
}

void UpdateButton(button_state_t *button, uint8_t isPressed) {
    if (button->state != isPressed) {
        button->transitionCounter++;

        if (button->transitionCounter >= 4) {
            button->state = isPressed;
            if (button->state != 0) {
                button->isPressed = 1;
            }
            button->transitionCounter = 0;
        }
    } else {
        button->transitionCounter = 0;
    }

}

void PollButtons() {
    uint8_t playButtonIsPressed = (BTN_PIN_REG & _BV(PLAY_BTN_PIN)) == 0;
    uint8_t plusButtonIsPressed = (BTN_PIN_REG & _BV(PLUS_BTN_PIN)) == 0;
    uint8_t minusButtonIsPressed = (BTN_PIN_REG & _BV(MINUS_BTN_PIN)) == 0;

    UpdateButton(&playButton, playButtonIsPressed);
    UpdateButton(&plusButton, plusButtonIsPressed);
    UpdateButton(&minusButton, minusButtonIsPressed);
}

int main() {
    SetupUart();
    EnableUartTransmission();
    SendStringToUart((char*)"Let the game begin!\r\n");

    SetOutputPins();
    SetupButtonPins();

    uint8_t pinToSet = activePin;

    while (1) {
        PollButtons();

        if (playButton.isPressed) {
            rotationIsClockWise = !rotationIsClockWise;
            playButton.isPressed = 0;
        }

        if (plusButton.isPressed) {
            if (cyclesPerLight > 0) {
                cyclesPerLight--;
            }
            plusButton.isPressed = 0;
        }

        if (minusButton.isPressed) {
            if (cyclesPerLight < 9) {
                cyclesPerLight++;
            }
            minusButton.isPressed = 0;
        }
        
        if (currentCycle >= cyclesPerLight) {
            if (rotationIsClockWise) {
                DecrementActiveLight();
            } else {
                IncrementActiveLight();
            }

            SetLightValue(pinToSet, 0);
            pinToSet = activePin;
            SetLightValue(pinToSet, 1);
            currentCycle = 0;
        }

        currentCycle++;
        _delay_ms(10);
    }
}
