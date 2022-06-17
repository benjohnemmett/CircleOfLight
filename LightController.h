#ifndef __LIGHT_CONTROLLER_H__
#define __LIGHT_CONTROLLER_H__

#include <avr/io.h>

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

class LightController {
    public:
        void SetupLights();
        void SetLightValue(uint8_t index, uint8_t value);
};

#endif