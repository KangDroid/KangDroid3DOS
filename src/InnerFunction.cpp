#include "main.h"

void InnerFunction::autoHomeSimulation() {
    int start_time;
    int end_time;

    // Home Z
    start_time = time(NULL);
    x_motor.enableStepper();
    while (!(digitalRead(ES_X) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 20) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            x_motor.rotateMotorInfinite(SPEED_MOTOR::SPEED_LOW);
        }
    }
    x_coord = 0;

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
    y_coord = 0;

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
    z_coord = 0; */
}

void InnerFunction::getGCodeInput() {
    cout << "GCode terminal Starts" << endl << "Input MOUT to end terminal menu." << endl;
    while (true) {
        getline(cin, test);
        pos = test.find(" ");
        // First parse value
        if (pos != -1) {
            first_bits = test.substr(0, pos); // The rest of them stored in test
            test.erase(0, pos + 1);
        } else {
            // Use test value
            first_bits.assign(test);
        }

        if (first_bits == "M119") {
            GCodeWrapper::M119();
        } else if (first_bits == "G28") {
            GCodeWrapper::G28();
        } else if (first_bits == "M18") {
            GCodeWrapper::M18();
        /*} else if (first_bits == "invert") {
            z_motor.invertDirection(); */
        } else if (first_bits == "G1") {
            int speed = 0, xmm = 0, ymm = 0, zmm = 0;
            if (seen('F')) {
                first_bits = first_bits.substr(1, test.find(" "));
                speed = stoi(first_bits);
            }
            if (seen('X')) {
                first_bits = first_bits.substr(1, test.find(" "));
                xmm = stoi(first_bits);
            }
            if (seen('Y')) {
                first_bits = first_bits.substr(1, test.find(" "));
                ymm = stoi(first_bits);
            }
            if (seen('Z')) {
                first_bits = first_bits.substr(1, test.find(" "));
                zmm = stoi(first_bits);
            }
            GCodeWrapper::G1(speed, xmm, ymm, zmm);
        } else if (first_bits == "MOUT") {
            break;
        } else {
            cout << "Unknown Command: \"" << test << "\"" << endl;
        }
    }
    cout << endl << endl;
}

bool InnerFunction::seen(char a) {
    pos = test.find(" ");
    if (test.find(a) != -1) {
        first_bits = test.substr(test.find(a), pos);
        test.erase(test.find(a), (pos == -1) ? pos : pos + 1);
        return true;
    } else {
        return false;
    }
}

void InnerFunction::showInfoAxis() {
    cout << "X: " << x_coord << endl;
    cout << "Y: " << y_coord << endl;
    cout << "Z: " << z_coord << endl;
}

void InnerFunction::moveAxis() {
    // Rotate Axis
    // if endstop switched -> Stop
    // Feedrate(Speed required)
}