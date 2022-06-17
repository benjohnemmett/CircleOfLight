#include "ButtonManager.h"

ButtonManager::ButtonManager() {
    this->SetupButtonPins();
    this->listener_ = 0;
}

void ButtonManager::SetListener(IButtonListener *listener) {
    this->listener_ = listener;
}

void ButtonManager::SetupButtonPins() {
    BTN_DDR &= ~_BV(PLAY_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(PLAY_BTN_PIN); // Set internal pull up resister

    BTN_DDR &= ~_BV(PLUS_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(PLUS_BTN_PIN); // Set internal pull up resister

    BTN_DDR &= ~_BV(MINUS_BTN_PIN); // Make sure DDR is set to input (0)
    BTN_PORT |= _BV(MINUS_BTN_PIN); // Set internal pull up resister
}

void ButtonManager::Update() {
    this->PollButtons();

    if (this->playButton.isPressed) {
        if (this->listener_ != 0) {
            this->listener_->PlayButtonPressed();
        }
        this->playButton.isPressed = 0;
    }
    if (this->plusButton.isPressed) {
        if (this->listener_ != 0) {
            this->listener_->PlusButtonPressed();
        }
        this->plusButton.isPressed = 0;
    }
    if (this->minusButton.isPressed) {
        if (this->listener_ != 0) {
            this->listener_->MinusButtonPressed();
        }
        this->minusButton.isPressed = 0;
    }
}

void ButtonManager::PollButtons() {
    uint8_t playButtonIsPressed = (BTN_PIN_REG & _BV(PLAY_BTN_PIN)) == 0;
    uint8_t plusButtonIsPressed = (BTN_PIN_REG & _BV(PLUS_BTN_PIN)) == 0;
    uint8_t minusButtonIsPressed = (BTN_PIN_REG & _BV(MINUS_BTN_PIN)) == 0;

    UpdateButton(&this->playButton, playButtonIsPressed);
    UpdateButton(&this->plusButton, plusButtonIsPressed);
    UpdateButton(&this->minusButton, minusButtonIsPressed);
}


void ButtonManager::UpdateButton(button_state_t *button, uint8_t isPressed) {
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