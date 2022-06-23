#ifndef _REFLEX_PROGRAM_H_
#define _REFLEX_PROGRAM_H_

#include "IProgram.h"
#include "LightController.h"
#include "ButtonManager.h"
#include "uart.h"

#define DISPLAY_BLINK_DURATION_TICKS 500
#define LIGHT_INDEX_1000S 1
#define LIGHT_INDEX_100S 2
#define LIGHT_INDEX_10S 3
#define LIGHT_INDEX_1S 4

enum ReflexProgramStateEnum {
    NONE,
    ENTRY,
    WAITING_FOR_BTN_PRESS,
    SPINNING,
    SCORE_TURN,
    DISPLAY_SCORE,
    EXIT
};

class ReflexProgramState {
    public:
        void Update() {
            this->update_ticks_in_current_state_++;
        }

        void ChangeToState(ReflexProgramStateEnum new_state) {
            this->current_state_ = new_state;
            #ifdef DEBUG_REFLEX_PROGRAM
            SendStringToUart((char*)"RP::Changing state to ");
            Print((uint8_t)new_state);
            SendStringToUart((char*)"\r\n");
            #endif
            this->update_ticks_in_current_state_ = 0;
        }

        ReflexProgramStateEnum CurrentState() {
            return this->current_state_;
        }

        uint16_t UpdateTicksInState() {
            return this->update_ticks_in_current_state_;
        }

        void ResetTicks() {
            this->update_ticks_in_current_state_ = 0;
        }

    private:
        ReflexProgramStateEnum current_state_ = NONE;
        uint16_t update_ticks_in_current_state_ = 0;
};

typedef struct {
    uint16_t score;
    uint16_t phase;
    uint8_t light_is_on;
} display_score_struct_t;

class ReflexProgram: public IProgram, public IButtonListener {
    public:
        ReflexProgram(LightController *light_controller, ButtonManager *button_manager);
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
        ReflexProgramState state;
        void HandleEntryUpdate();
        void HandleWaitingForButtonPress();
        void HandleSpinningUpdate();
        void HandleScoreTurnUpdate();
        void HandleDisplayScoreUpdate();
        void HandleExitUpdate();

        void IncrementActiveLightIndex() { this->active_light_index_ = (this->active_light_index_ % 12) + 1; }
        uint8_t GetCyclesPerLight() { return this->cycles_per_light_array_[this->cycles_per_light_index_]; }

        uint8_t active_light_index_;
        const uint8_t cycles_per_light_array_[5] = {40, 60, 80, 100, 120};
        const uint8_t cycles_per_light_array_length_ = 5;
        uint8_t cycles_per_light_index_ = 2;
                                        // 1   2  3    4   5   6    7  8  9  10   11   12
        int8_t light_score_mapping_[12] = {-10, 5, 25,  5, -1, 50,  -1, 5, 25, 5, -10, 100};
        int16_t score_;
        uint8_t turn_;

        uint8_t toggle_light_state_;
        uint8_t game_is_running_;
        display_score_struct_t display_score_struct_;

};

#endif