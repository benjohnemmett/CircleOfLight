#include "CountDownTimerProgram.h"

CountDownTimerProgram::CountDownTimerProgram(LightController *light_controller, ButtonManager *button_manager) {
    this->light_controller_ = light_controller;
    this->button_manager_ = button_manager;
}

void CountDownTimerProgram::SetupProgram() {
    this->light_controller_->SetupLights();
    this->button_manager_->SetListener(this);
}

void CountDownTimerProgram::Update() {}
void CountDownTimerProgram::TearDownProgram() {}
bool CountDownTimerProgram::IsDoneRunning() {
    return false;
}

void CountDownTimerProgram::PlayButtonPressed() {}
void CountDownTimerProgram::PlusButtonPressed() {}
void CountDownTimerProgram::MinusButtonPressed() {}
void CountDownTimerProgram::PlayButtonReleased() {}
void CountDownTimerProgram::PlusButtonReleased() {}
void CountDownTimerProgram::MinusButtonReleased() {}
