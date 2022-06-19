
#include <util/delay.h>
#include "uart.h"
#include "LightController.h"
#include "ReflexProgram.h"
#include "ButtonManager.h"
#include "MenuProgram.h"

ButtonManager buttonManager;
LightController lightController;
ReflexProgram reflexProgram(&lightController, &buttonManager);

IProgram *runningProgram;

MenuProgram menuProgram(&lightController, &buttonManager, &runningProgram);

int main() {
    SetupUart();
    EnableUartTransmission();

    SendStringToUart((char*)"Adding Reflex Program\r\n");
    menuProgram.AddProgram(&reflexProgram);

    SendStringToUart((char*)"Setting up menu program\r\n");
    runningProgram = &menuProgram;
    runningProgram->SetupProgram();

    SendStringToUart((char*)"Entering loop\r\n");
    while (1) {
        buttonManager.Update();
        runningProgram->Update();

        if (runningProgram->IsDoneRunning()) {
            runningProgram->TearDownProgram();
            runningProgram = &menuProgram;
            runningProgram->SetupProgram();
        }

        _delay_ms(1);
    }
}
