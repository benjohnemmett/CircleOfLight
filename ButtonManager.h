#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

#include <avr/io.h>

#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN_REG PIND
#define PLAY_BTN_PIN PD4
#define MINUS_BTN_PIN PD3
#define PLUS_BTN_PIN PD2

typedef struct {
    uint8_t state;
    uint8_t transitionCounter;
    uint8_t isPressed;
    uint8_t isReleased;
} button_state_t;

class IButtonListener {
    public:
        virtual void PlayButtonPressed();
        virtual void PlusButtonPressed();
        virtual void MinusButtonPressed();
        virtual void PlayButtonReleased();
        virtual void PlusButtonReleased();
        virtual void MinusButtonReleased();
};

class ButtonManager {
    public:
        ButtonManager();
        void Update();
        void SetListener(IButtonListener *listener);

    private:
        void SetupButtonPins();
        void PollButtons();
        void UpdateButton(button_state_t *button, uint8_t isPressed);
        button_state_t playButton = {0, 0, 0};
        button_state_t plusButton = {0, 0, 0};
        button_state_t minusButton = {0, 0, 0};
        IButtonListener *listener_;
};

#endif