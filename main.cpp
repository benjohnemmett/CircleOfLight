
#include <util/delay.h>
#include "uart.h"
#include "LightController.h"
#include "ReflexProgram.h"
#include "ButtonManager.h"

ButtonManager buttonManager;
LightController lightController;
ReflexProgram reflexProgram(&lightController, &buttonManager);

int main() {
    SetupUart();
    EnableUartTransmission();
    SendStringToUart((char*)"Let the game begin!\r\n");

    reflexProgram.SetupProgram();

    while (1) {
        buttonManager.Update();
        reflexProgram.Update();
        _delay_ms(10);
    }
}
