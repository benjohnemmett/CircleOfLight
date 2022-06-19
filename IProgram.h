#ifndef _I_PROGRAM_H_
#define _I_PROGRAM_H_

class IProgram {
    public:
        virtual void SetupProgram() = 0;
        virtual void Update() = 0;
        virtual void TearDownProgram() = 0;
        virtual bool IsDoneRunning() = 0;
};

#endif