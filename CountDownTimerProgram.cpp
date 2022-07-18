#include "CountDownTimerProgram.h"

CountDownTimerProgram::CountDownTimerProgram(LightController *light_controller, ButtonManager *button_manager) {
    this->light_controller_ = light_controller;
    this->button_manager_ = button_manager;
}

void CountDownTimerProgram::SetupProgram() {
    this->light_controller_->SetupLights();
    this->button_manager_->SetListener(this);
    this->state.ChangeState(COUNTDOWN_TIMER_STATE_ENTRY);
    this->program_is_running_ = 1;
}

void CountDownTimerProgram::Update() {
    switch(this->state.CurrentState()) {
        case COUNTDOWN_TIMER_STATE_ENTRY:
            this->HandleEntryUpdate();
            break;
        case COUNTDOWN_TIMER_STATE_SET_TIME:
            this->HandleSetTimeUpdate();
            break;
        case COUNTDOWN_TIMER_STATE_COUNTING_DOWN:
            this->HandleCountingDownUpdate();
            break;
        case COUNTDOWN_TIMER_STATE_TIMES_UP:
            this->HandleTimesUpUpdate();
            break;
    }
    this->state.Update();
}

void CountDownTimerProgram::TearDownProgram() {
    this->light_controller_->ClearAllLights();
}

bool CountDownTimerProgram::IsDoneRunning() {
    return !program_is_running_;
}

void CountDownTimerProgram::HandleEntryUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks % 64 == 0) {
        uint8_t light_to_activate = (ticks / 64) + 6;
        uint8_t other_light;
        if (light_to_activate < 12) {
            other_light = 12 - light_to_activate;
        }

        if (light_to_activate >= 12) {
            this->light_controller_->ClearAllLights();
            this->state.ChangeState(COUNTDOWN_TIMER_STATE_SET_TIME);
            this->set_time_struct_.light_index = 1;
            this->set_time_struct_.light_is_on = 0;
        } else {
            this->light_controller_->ClearAllLights();
            this->light_controller_->SetLightValue(light_to_activate, 1);
            this->light_controller_->SetLightValue(other_light, 1);
        }
    }
}

void CountDownTimerProgram::HandleSetTimeUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks > SET_TIME_BLINK_TICKS) {
        this->set_time_struct_.light_is_on = !this->set_time_struct_.light_is_on;
        if (this->set_time_struct_.light_is_on) {
            this->light_controller_->ClearAllLights();
        } else {
            this->light_controller_->SetLightValue(this->set_time_struct_.light_index, 1);
        }
    }
}

void CountDownTimerProgram::HandleCountingDownUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (this->countdown_struct_.miliseconds == 0) {
        if (this->countdown_struct_.seconds == 0) {
            if (this->countdown_struct_.minutes == 0) {
                this->state.ChangeState(COUNTDOWN_TIMER_STATE_TIMES_UP);
            } else {
                this->countdown_struct_.minutes--;
                this->countdown_struct_.seconds = 59;
            }
        } else {
            this->countdown_struct_.seconds--;
        }
        this->countdown_struct_.miliseconds = 999;

        if (this->countdown_struct_.light_is_on) {
            this->light_controller_->ClearAllLights();
            this->countdown_struct_.light_is_on = 0;
        } else {
            uint8_t light_to_turn_on = this->countdown_struct_.minutes;
            if (light_to_turn_on == 0) {
                light_to_turn_on = 12;
            }
            this->light_controller_->SetLightValue(light_to_turn_on, 1);
            this->countdown_struct_.light_is_on = 1;
        }
    }

    this->countdown_struct_.miliseconds--;
}

void CountDownTimerProgram::HandleTimesUpUpdate() {
    uint16_t ticks = this->state.UpdateTicksInState();

    if (ticks % 64 == 0) {
        uint8_t light_to_activate = (ticks / 64) + 1;
        uint8_t other_light;
        if (light_to_activate < 12) {
            other_light = 12 - light_to_activate;
        }

        if (light_to_activate >= 12) {
            times_up_cyles_++;
            if (times_up_cyles_ > 10) {
                this->state.ChangeState(COUNTDOWN_TIMER_STATE_ENTRY);
            }
            this->state.ResetTicks();
        }
        
        this->light_controller_->ClearAllLights();
        this->light_controller_->SetLightValue(light_to_activate, 1);
        this->light_controller_->SetLightValue(other_light, 1);
        
    }
}

void CountDownTimerProgram::HandleExitUpdate() {
    this->program_is_running_ = 0;
}

void CountDownTimerProgram::PlayButtonPressed() {
    switch(this->state.CurrentState()) {
        case COUNTDOWN_TIMER_STATE_SET_TIME:
            this->countdown_struct_.miliseconds = 0;
            this->countdown_struct_.seconds = 0;
            this->countdown_struct_.minutes = this->set_time_struct_.light_index;
            this->countdown_struct_.light_is_on = 0;
            this->light_controller_->ClearAllLights();
            this->state.ChangeState(COUNTDOWN_TIMER_STATE_COUNTING_DOWN);
            break;
        case COUNTDOWN_TIMER_STATE_EXIT:
            this->program_is_running_ = 0;
            break;
    }
}

void CountDownTimerProgram::PlusButtonPressed() {
    switch (this->state.CurrentState()) {
        case COUNTDOWN_TIMER_STATE_SET_TIME:
            this->set_time_struct_.light_index++;
            if (this->set_time_struct_.light_index > 12) {
                this->set_time_struct_.light_index = 1;
            }
            break;
    }
}

void CountDownTimerProgram::MinusButtonPressed() {
    switch (this->state.CurrentState()) {
        case COUNTDOWN_TIMER_STATE_SET_TIME:
            this->set_time_struct_.light_index--;
            if (this->set_time_struct_.light_index < 1) {
                this->set_time_struct_.light_index = 12;
            }
            break;
    }
}

void CountDownTimerProgram::PlayButtonReleased() {}
void CountDownTimerProgram::PlusButtonReleased() {}
void CountDownTimerProgram::MinusButtonReleased() {}
