#ifndef _TEST_PROGRAM_H_
#define _TEST_PROGRAM_H_

#include "IProgram.h"
#include "LightController.h"
#include "ButtonManager.h"

class TestProgram: public IProgram, public IButtonListener {
    public:
        TestProgram(LightController *light_controller, ButtonManager *button_manager);
        void SetupProgram();
        void Update();
        void TearDownProgram();
        bool IsDoneRunning();

        void PlusButtonPressed();
        void PlayButtonPressed();
        void MinusButtonPressed();
        void PlayButtonReleased();
        void PlusButtonReleased();
        void MinusButtonReleased();

    private:
        LightController *light_controller_;
        ButtonManager *button_manager_;
        uint8_t current_cycle_;
        uint8_t cycles_per_light_;
        uint8_t rotation_is_clockwise_;
        uint8_t active_pin_index_;
        uint8_t program_is_done_;
        const uint8_t MIN_CYCLES_PER_LIGHT = 20;
        const uint8_t MAX_CYCLES_PER_LIGHT = 80;
        const uint8_t CYCLES_PER_LIGHT_STEP = 15;
};

#endif