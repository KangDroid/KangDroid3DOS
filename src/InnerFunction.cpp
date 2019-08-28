#include "main.h"

void InnerFunction::autoHomeSimulation() {
    int start_time;
    int end_time;

    // Home X
    start_time = time(NULL);
    while (!(digitalRead(pin_es_array[0]) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 5) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            clearScreen();
            cout << "Moving X..." << endl;
        }
    }

    // Home Y
    start_time = time(NULL);
    while (!(digitalRead(pin_es_array[1]) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 5) {
            // Failed
        } else {
            clearScreen();
            cout << "Moving Y..." << endl;
        }
    }

    // Home Z
    start_time = time(NULL);
    while (!(digitalRead(pin_es_array[2]) == false)) {
        end_time = time(NULL);
        
        if ((end_time - start_time) == 5) {
            // Failed
        } else {
            clearScreen();
            cout << "Moving Z..." << endl;
        }
    }
}

void InnerFunction::testEndstopPin() {
    cout << "Current PIN Status:" << endl;
    for (int i = 0; i < es_pin_count; i++) {
        cout << "PIN: " << pin_es_array[i] << ((digitalRead(pin_es_array[i]) == false) ? ": PROBED" : ": UNPROBED") << endl;
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

void InnerFunction::moveAxis() {
    // Rotate Axis
    // if endstop switched -> Stop
    // Feedrate(Speed required)
}