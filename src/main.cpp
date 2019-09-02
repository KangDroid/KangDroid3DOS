#include "main.h"

int main(void) {
    int menu_val;
    // Implementation
    wiringPiSetup();
    EndstopClass es(PUD_UP);
    es.initPin(); //Shouldn't be destroied

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

int sendSignal(int cause) {
    switch (cause) {
        case INTERRUPT_CODE::AUTO_HOME_FAILED:
            cout << "Homing Failed!!" << endl << "Exiting Program!" << endl;
            GCodeWrapper::M18();
            exit(1); 
        break;
        case INTERRUPT_CODE::SIG_OK:
        break;
    }
    return cause;
}

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
void clearScreen() {
    system("clear && printf '\e[3J'");
}
#endif