#ifndef _COUNT_DOWN_TIMER_PROGRAM_H_
#define _COUNT_DOWN_TIMER_PROGRAM_H_

#include "LightController.h"
#include "ButtonManager.h"
#include "StateMachine.h"
#include "IProgram.h"

#define SET_TIME_BLINK_TICKS 300

enum CountdownTimerStateEnum {
    COUNTDOWN_TIMER_STATE_NONE,
    COUNTDOWN_TIMER_STATE_ENTRY,
    COUNTDOWN_TIMER_STATE_SET_TIME,
    COUNTDOWN_TIMER_STATE_COUNTING_DOWN,
    COUNTDOWN_TIMER_STATE_TIMES_UP,
    COUNTDOWN_TIMER_STATE_EXIT,
};

typedef struct {
    uint8_t light_is_on;
    uint8_t light_index;
} set_time_struct_t;

typedef struct {
    uint8_t minutes;
    uint8_t seconds;
    uint16_t miliseconds;
    uint8_t light_is_on;
} countdown_struct_t;

class CountDownTimerProgram: public IProgram, public IButtonListener {
    public:
        CountDownTimerProgram(LightController *light_controller, ButtonManager *button_manager);
        void SetupProgram();
        void Update();
        void TearDownProgram();
        bool IsDoneRunning();

        void HandleEntryUpdate();
        void HandleSetTimeUpdate();
        void HandleCountingDownUpdate();
        void HandleTimesUpUpdate();
        void HandleExitUpdate();

        void PlusButtonPressed();
        void MinusButtonPressed();
        void PlayButtonPressed();
        void PlusButtonReleased();
        void MinusButtonReleased();
        void PlayButtonReleased();

    private:
        LightController *light_controller_;
        ButtonManager *button_manager_;
        StateMachine<CountdownTimerStateEnum> state;
        set_time_struct_t set_time_struct_;
        countdown_struct_t countdown_struct_;
        uint8_t program_is_running_;
        uint8_t times_up_cyles_;
};

#endif