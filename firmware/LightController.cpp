#include "LightController.h"

void LightController::SetupLights() {
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

void LightController::SetLightValue(uint8_t index, uint8_t value) {
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

void LightController::ClearAllLights() {
    LIGHT_01_PORT &= ~_BV(LIGHT_01_PIN);
    LIGHT_02_PORT &= ~_BV(LIGHT_02_PIN);
    LIGHT_03_PORT &= ~_BV(LIGHT_03_PIN);
    LIGHT_04_PORT &= ~_BV(LIGHT_04_PIN);
    LIGHT_05_PORT &= ~_BV(LIGHT_05_PIN);
    LIGHT_06_PORT &= ~_BV(LIGHT_06_PIN);
    LIGHT_07_PORT &= ~_BV(LIGHT_07_PIN);
    LIGHT_08_PORT &= ~_BV(LIGHT_08_PIN);
    LIGHT_09_PORT &= ~_BV(LIGHT_09_PIN);
    LIGHT_10_PORT &= ~_BV(LIGHT_10_PIN);
    LIGHT_11_PORT &= ~_BV(LIGHT_11_PIN);
    LIGHT_12_PORT &= ~_BV(LIGHT_12_PIN);
}
