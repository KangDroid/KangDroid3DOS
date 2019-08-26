#include "main.h"

int showMenu();
void getGCodeInput();

int main(void) {
    int menu_val;
    // Implementation
    initPinsGPIO();

    do {
        menu_val = showMenu();
        switch(menu_val) {
            case 1:
                clearScreen();
                InnerFunction::testEndstopPin();
            break;
            case 2:
                clearScreen();
                InnerFunction::autoHomeSimulation();
            break;
            case 3:
                clearScreen();
                InnerFunction::getGCodeInput();
            break;
        }
    } while(menu_val != 0);
    return 0;
}

int showMenu() {
    int ret_val;

    cout << "1. Test Endstop PIN" << endl;
    cout << "2. Auto Home Simulation" << endl;
    cout << "3. Custom GCode terminal" << endl;
    cout << "0. Quit" << endl;
    cin >> ret_val;

    return ret_val;
}

void initPinsGPIO() {
    wiringPiSetup();
    EndstopClass es(pin_array, INPUT, PUD_UP);
    es.initPin();
}