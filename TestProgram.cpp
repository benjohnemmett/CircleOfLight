#include "TestProgram.h"

TestProgram::TestProgram(LightController *light_controller, ButtonManager *button_manager) {
    this->light_controller_ = light_controller;
    this->button_manager_ = button_manager;
    this->cycles_per_light_ = 50;
}

void TestProgram::SetupProgram() {
    this->light_controller_->SetupLights();
    this->button_manager_->SetListener(this);
}

void TestProgram::Update() {
    uint8_t previous_pin = active_pin_index_;

    if (current_cycle_ >= cycles_per_light_) {
        if (rotation_is_clockwise_) {
            if (active_pin_index_ > 1) {
                active_pin_index_--;
            } else {
                active_pin_index_ = 12;
            }
        } else {
            active_pin_index_ += 1;
            if (active_pin_index_ > 12) {
                active_pin_index_ = 1;
            }
        }

        this->light_controller_->SetLightValue(previous_pin, 0);
        this->light_controller_->SetLightValue(active_pin_index_, 1);
        current_cycle_ = 0;
    }

    current_cycle_++;
}

void TestProgram::TearDownProgram() {

}

bool TestProgram::IsDoneRunning() {
    return false;
}

void TestProgram::PlusButtonPressed() {
    if (this->cycles_per_light_ > this->MIN_CYCLES_PER_LIGHT) {
        this->cycles_per_light_ -= this->CYCLES_PER_LIGHT_STEP;
    }
}

void TestProgram::PlayButtonPressed() {
    rotation_is_clockwise_ = !rotation_is_clockwise_;
}

void TestProgram::MinusButtonPressed() {
    if (this->cycles_per_light_ < this->MAX_CYCLES_PER_LIGHT) {
        this->cycles_per_light_ += this->CYCLES_PER_LIGHT_STEP;
    }
}