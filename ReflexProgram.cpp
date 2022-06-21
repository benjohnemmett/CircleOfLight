#include "ReflexProgram.h"

ReflexProgram::ReflexProgram(LightController *light_controller, ButtonManager *button_manager) {
    this->light_controller_ = light_controller;
    this->button_manager_ = button_manager;
    this->game_is_running_ = 1;
}

void ReflexProgram::SetupProgram() {
    this->light_controller_->SetupLights();
    this->button_manager_->SetListener(this);
    this->state.ChangeToState(ENTRY);
    this->cycles_per_light_index_ = 2;
    this->score_ = 0;
    this->turn_ = 0;
    this->game_is_running_ = 1;
}

void ReflexProgram::Update() {

    switch(this->state.CurrentState()) {
        case ENTRY:
            this->HandleEntryUpdate();
            break;
        case WAITING_FOR_BTN_PRESS:
            this->HandleWaitingForButtonPress();
            break;
        case SPINNING:
            this->HandleSpinningUpdate();
            break;
        case SCORE_TURN:
            this->HandleScoreTurnUpdate();
            break;
        case DISPLAY_SCORE:
            this->HandleDisplayScoreUpdate();
            break;
        case EXIT:
            this->HandleExitUpdate();
    }

    this->state.Update();
}

void ReflexProgram::HandleEntryUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks % 64 == 0) {
        uint8_t light_to_activate = (ticks / 64) + 6;
        uint8_t other_light;
        if (light_to_activate < 12) {
            other_light = 12 - light_to_activate;
        }

        if (light_to_activate >= 12) {
            this->light_controller_->ClearAllLights();
            this->state.ChangeToState(WAITING_FOR_BTN_PRESS);
        } else {
            this->light_controller_->ClearAllLights();
            this->light_controller_->SetLightValue(light_to_activate, 1);
            this->light_controller_->SetLightValue(other_light, 1);
        }
    }
}

void ReflexProgram::HandleWaitingForButtonPress() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks >= GetCyclesPerLight()) {
        this->toggle_light_state_ = !this->toggle_light_state_;
        this->light_controller_->SetLightValue(12, this->toggle_light_state_);
        this->state.ResetTicks();
    }
}

void ReflexProgram::HandleSpinningUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks >= GetCyclesPerLight()) {
        this->light_controller_->SetLightValue(this->active_light_index_, 0);
        this->IncrementActiveLightIndex();
        this->light_controller_->SetLightValue(this->active_light_index_, 1);
        
        this->state.ResetTicks();
    }
}

void ReflexProgram::HandleScoreTurnUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks > 6*256) {
        this->light_controller_->ClearAllLights();
        if (this->turn_ < 3) {
            this->state.ChangeToState(WAITING_FOR_BTN_PRESS);
        } else {
            this->state.ChangeToState(DISPLAY_SCORE);
        }
    }

    if (ticks % 256 == 0) {
        this->toggle_light_state_ = !this->toggle_light_state_;
        this->light_controller_->SetLightValue(this->active_light_index_, this->toggle_light_state_);
    }
}

void ReflexProgram::HandleDisplayScoreUpdate() {

    SendStringToUart((char*)"RP::Game over. Score - ");
    Print((uint16_t)this->score_);
    SendStringToUart((char*)"\r\n");

    this->state.ChangeToState(EXIT);
}

void ReflexProgram::HandleExitUpdate() {
        uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks % 64 == 0) {
        uint8_t light_to_activate = (ticks / 64) + 1;
        uint8_t other_light;
        if (light_to_activate < 12) {
            other_light = 12 - light_to_activate;
        }

        if (light_to_activate >= 7) {
            this->light_controller_->ClearAllLights();
            this->game_is_running_ = 0;
        } else {
            this->light_controller_->ClearAllLights();
            this->light_controller_->SetLightValue(light_to_activate, 1);
            this->light_controller_->SetLightValue(other_light, 1);
        }
    }
}

void ReflexProgram::TearDownProgram() {
    this->light_controller_->ClearAllLights();
}

bool ReflexProgram::IsDoneRunning() {
    return !this->game_is_running_;
}


void ReflexProgram::PlayButtonPressed() {
    switch(this->state.CurrentState()) {
        case WAITING_FOR_BTN_PRESS:
            this->turn_++;
            this->light_controller_->ClearAllLights();
            this->state.ChangeToState(SPINNING);
            break;
    }
}

void ReflexProgram::PlusButtonPressed() {
    if (this->cycles_per_light_index_ > 0) {
        this->cycles_per_light_index_--;
    }
}

void ReflexProgram::MinusButtonPressed() {
    if (this->cycles_per_light_index_ < this->cycles_per_light_array_length_ - 1) {
        this->cycles_per_light_index_++;
    }
}

void ReflexProgram::PlayButtonReleased() {
        switch(this->state.CurrentState()) {
        case SPINNING:
            uint8_t multiplier = this->cycles_per_light_array_length_ - this->cycles_per_light_index_;
            int16_t points = multiplier * (int16_t)light_score_mapping_[active_light_index_ - 1];
            this->score_ += points;
            if (this->score_ < 0) {
                this->score_ = 0;
            }
            this->state.ChangeToState(SCORE_TURN);
            break;
    }
}

void ReflexProgram::PlusButtonReleased() {}
void ReflexProgram::MinusButtonReleased() {}