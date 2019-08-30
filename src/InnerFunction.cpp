#include "main.h"

void InnerFunction::autoHomeSimulation() {
    int start_time;
    int end_time;

    // Home X
    start_time = time(NULL);
    mcc.enableStepper();
    while (!(digitalRead(ES_X) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 20) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            mcc.rotateMotorInfinite(SPEED_MOTOR::SPEED_LOW);
        }
    }

    // Home Y
    /*start_time = time(NULL);
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
    }*/
}

void InnerFunction::testEndstopPin() {
    cout << "Current PIN Status:" << endl;
    cout << "PIN: " << ES_X << ((digitalRead(ES_X) == false) ? ": PROBED" : ": UNPROBED") << endl;
    cout << "PIN: " << ES_Y << ((digitalRead(ES_Y) == false) ? ": PROBED" : ": UNPROBED") << endl;
    cout << "PIN: " << ES_Z << ((digitalRead(ES_Z) == false) ? ": PROBED" : ": UNPROBED") << endl;
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
        } else if (!strcmp(test, "M18")) {
            GCodeWrapper::M18();
        } else if (!strcmp(test, "invert")) {
            mcc.invertDirection();
        } else if (!strcmp(test, "G1")) {
            GCodeWrapper::G1();
        } else if (!strcmp(test, "MOUT")) {
            break;
        } else {
            cout << "Unknown Command: \"" << test << "\"" << endl;
        }
    }
    cout << endl << endl;
}

void InnerFunction::moveAxis() {
    // Rotate Axis
    // if endstop switched -> Stop
    // Feedrate(Speed required)
}