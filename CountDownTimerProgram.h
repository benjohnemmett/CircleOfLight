#ifndef _COUNT_DOWN_TIMER_PROGRAM_H_
#define _COUNT_DOWN_TIMER_PROGRAM_H_

#include "LightController.h"
#include "ButtonManager.h"
#include "IProgram.h"

class CountDownTimerProgram: public IProgram, public IButtonListener {
    public:
        CountDownTimerProgram(LightController *light_controller, ButtonManager *button_manager);
        void SetupProgram();
        void Update();
        void TearDownProgram();
        bool IsDoneRunning();

        void PlusButtonPressed();
        void MinusButtonPressed();
        void PlayButtonPressed();
        void PlusButtonReleased();
        void MinusButtonReleased();
        void PlayButtonReleased();

    private:
        LightController *light_controller_;
        ButtonManager *button_manager_;
};

#endif