#ifndef _MENU_PROGRAM_H_
#define _MENU_PROGRAM_H_

#include "IProgram.h"
#include "LightController.h"
#include "ButtonManager.h"
#include "uart.h"

class MenuProgram: public IProgram, public IButtonListener {
    public:
        MenuProgram(LightController *light_controller, 
            ButtonManager *button_manager,
            IProgram **running_program);
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

        void AddProgram(IProgram *program);

    private:
        IProgram **running_program_;
        uint8_t active_pin_index_;
        LightController *light_controller_;
        ButtonManager *button_manager_;
        uint8_t enable_lights_ = 0;
        IProgram *program_list_[12];
        uint8_t program_list_index_ = 0;
        uint8_t update_tick_ = 0;
        uint8_t light_brightness_ = 2;
        uint8_t pulse_direction_is_up;
        uint8_t clear_light_index_ = 0;
};

#endif