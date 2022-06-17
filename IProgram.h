#ifndef _I_PROGRAM_H_
#define _I_PROGRAM_H_

class IProgram {
    public:
        virtual void SetupProgram() = 0;
        virtual void Update() = 0;
        virtual void StopProgram() = 0;
};

#endif