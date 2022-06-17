#ifndef _REFLEX_PROGRAM_H_
#define _REFLEX_PROGRAM_H_

#include "IProgram.h"
#include "LightController.h"
#include "ButtonManager.h"

class ReflexProgram: public IProgram, public IButtonListener {
    public:
        ReflexProgram(LightController *light_controller, ButtonManager *button_manager);
        void SetupProgram();
        void Update();
        void StopProgram();

        void PlusButtonPressed();
        void PlayButtonPressed();
        void MinusButtonPressed();

    private:
        LightController *light_controller_;
        ButtonManager *button_manager_;
        uint8_t current_cycle_;
        uint8_t cycles_per_light_;
        uint8_t rotation_is_clockwise_;
        uint8_t active_pin_index_;
};

#endif