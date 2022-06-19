#include "MenuProgram.h"

MenuProgram::MenuProgram(LightController *light_controller, 
                        ButtonManager *button_manager,
                        IProgram **running_program) {
    this->running_program_ = running_program;
    this->light_controller_ = light_controller;
    this->button_manager_ = button_manager;
    this->active_pin_index_ = 12;
    this->enable_lights_ = 0;
    this->update_tick_ = 0;
    this->light_brightness_ = 2;
    this->pulse_direction_is_up = 1;
}

void MenuProgram::SetupProgram() {
    this->light_controller_->SetupLights();
    this->button_manager_->SetListener(this);
}

void MenuProgram::Update() {
    if (this->clear_light_index_) {
        this->light_controller_->SetLightValue(this->clear_light_index_, 0);
        this->clear_light_index_ = 0;
    }

    uint8_t index = this->active_pin_index_ % 12;
    uint8_t current_index_has_program = this->program_list_[index] != 0;
    if (current_index_has_program) {
        enable_lights_ = this->update_tick_ % light_brightness_;
    } else {
        enable_lights_ = this->update_tick_ % 2;
    }

    this->light_controller_->SetLightValue(active_pin_index_, enable_lights_);


    this->update_tick_++;

    if (this->update_tick_ % 128) {
        if (this->light_brightness_ > 5) {
            this->pulse_direction_is_up = 0;
        } else if (this->light_brightness_ < 3) {
            this->pulse_direction_is_up = 1;
        }

        if (this->pulse_direction_is_up) {
            this->light_brightness_++;
        } else {
            this->light_brightness_--;
        }
    }
}

void MenuProgram::TearDownProgram() {
    this->light_controller_->ClearAllLights();
}

bool MenuProgram::IsDoneRunning() {
    return false;
}

void MenuProgram::PlayButtonPressed() {
    SendStringToUart((char*)"MenuProgram:: PlayButton pressed\r\n");
    if (this->program_list_index_ > 0) {
        uint8_t index = this->active_pin_index_ % 12;
        if (this->program_list_[index] != 0) {
            this->TearDownProgram();
            *this->running_program_ = this->program_list_[index];
            (*this->running_program_)->SetupProgram();
        }
    }
}

void MenuProgram::PlusButtonPressed() {
    this->clear_light_index_ = active_pin_index_;
    active_pin_index_ = (active_pin_index_ % 12) + 1;
}

void MenuProgram::MinusButtonPressed() {
    this->clear_light_index_ = active_pin_index_;
    if (this->active_pin_index_ == 1) {
        this->active_pin_index_ = 12;
    } else {
        this->active_pin_index_--;
    }
}

void MenuProgram::AddProgram(IProgram *program) {
    this->program_list_[this->program_list_index_] = program;
    this->program_list_index_++;
}