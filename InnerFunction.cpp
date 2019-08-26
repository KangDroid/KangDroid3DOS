#include "main.h"

void InnerFunction::autoHomeSimulation() {
    // Home X
    while (!(digitalRead(pin_array[0]) == false)) {
        clearScreen();
        cout << "Moving X..." << endl;
    }
    // Home Y
    while (!(digitalRead(pin_array[1]) == false)) {
        clearScreen();
        cout << "Moving Y..." << endl;
    }
    // Home Z
    while (!(digitalRead(pin_array[2]) == false)) {
        clearScreen();
        cout << "Moving Z..." << endl;
    }
}

void InnerFunction::testEndstopPin() {
    cout << "Current PIN Status:" << endl;
    for (int i = 0; i < ENDSTOP_PIN_COUNT; i++) {
        cout << "PIN: " << pin_array[i] << ((digitalRead(pin_array[i]) == false) ? ": PROBED" : ": UNPROBED") << endl;
    }
    cout << endl << endl;
}

void InnerFunction::getGCodeInput() {
    char test[256];
    cout << "GCode terminal Starts" << endl << "Input MOUT to end terminal menu." << endl;
    while (true) {
        cin >> test;
        if (!strcmp(test, "M119")) {
            GCodeWrapper::M119();
        } else if(!strcmp(test, "G28")) {
            GCodeWrapper::G28();
        } else if (!strcmp(test, "MOUT")) {
            break;
        }
    }
    cout << endl << endl;
}