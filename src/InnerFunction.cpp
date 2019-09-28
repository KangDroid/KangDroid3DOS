#include "main.h"
#include "global.h"

/**
 * Auto Homing Mechanism:
 * basically motor moves to minimum endstop(which means axis should go to 0)
 * if endstop detected, motor slowly(reverse about a few millimetre, and slowly detect endstop again)
 * Putting move(axis) to -10 so it will go infinite
 */ 
void InnerFunction::autoHomeSimulation() {
    int start_time;
    int end_time;

    // Home X
    start_time = time(NULL);
    x_motor->enableStepper();

    /*X/Y Motor direction changes because it is corexy*/
    digitalWrite(y_motor->retDir(), LOW);
    digitalWrite(x_motor->retDir(), HIGH);
    //TODO: Surround those digitalWrite with function or somehow implement it --> Beautify

    while (!(digitalRead(ES_X) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 20) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            axis->moveAxisInf(SPEED_MOTOR::SPEED_MID); // Only for COREXY Devices
        }
    }
    coord->setX(0);

    // Home Y
    start_time = time(NULL);

    /*X/Y Motor direction changes because it is corexy*/
    digitalWrite(y_motor->retDir(), LOW);
    digitalWrite(x_motor->retDir(), LOW);
    //TODO: Surround those digitalWrite with function or somehow implement it --> Beautify

    while (!(digitalRead(ES_Y) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 20) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            axis->moveAxisInf(SPEED_MOTOR::SPEED_MID); // Only for COREXY Devices
        }
    }
    coord->setY(0);

    // Home Z
    /*start_time = time(NULL);
    while (!(digitalRead(pin_es_array[2]) == false)) {
        end_time = time(NULL);
        
        if ((end_time - start_time) == 5) {
            // Failed
        } else {
            clearScreen();
            cout << "Moving Z..." << endl;
        }
    }
    coord.setZ(0);; */
}

void InnerFunction::getGCodeInput() {
    cout << "GCode terminal Starts" << endl << "Input MOUT to end terminal menu." << endl;
    // Clear Buffer
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
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
        } else if (first_bits == "M114") {
            GCodeWrapper::M114();
        } else if (first_bits == "HOME") {
            coord->setX(0);
            coord->setY(0);
            coord->setZ(0);
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
    cout << "Current Location Information:" << endl;
    cout << "X: " << coord->retX() << endl;
    cout << "Y: " << coord->retY() << endl;
    cout << "Z: " << coord->retZ() << endl;
}

void InnerFunction::moveAxis() {
    // Rotate Axis
    // if endstop switched -> Stop
    // Feedrate(Speed required)
}