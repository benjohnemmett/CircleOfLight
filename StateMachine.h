#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

template <class T>
class StateMachine {
    public:
        void Update() {
            this->update_ticks_in_current_state_++;
        }

        void ChangeState(T new_state) {
            this->current_state_ = new_state;
            this->update_ticks_in_current_state_ = 0;
        }

        T CurrentState() {
            return this->current_state_;
        }

        uint16_t UpdateTicksInState() {
            return this->update_ticks_in_current_state_;
        }

        void ResetTicks() {
            this->update_ticks_in_current_state_ = 0;
        }

    private:
        T current_state_;
        uint16_t update_ticks_in_current_state_;
};

#endif // _STATE_MACHINE_H_