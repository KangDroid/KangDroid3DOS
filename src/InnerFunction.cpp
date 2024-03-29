/**
 * Copyright (C) 2019, Jason HW Kang(Aka. KangDroid, Hyun Woo Kang)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * If any violation of this project found, please contact to kangdroid@konkuk.ac.kr
 */

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
    Timer::TIMER_Init();
    axis->enableStepper();

    // Home X
    start_time = time(NULL);
    //x_motor->enableStepper();

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
    digitalWrite(y_motor->retDir(), HIGH);
    digitalWrite(x_motor->retDir(), HIGH);
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
    digitalWrite(z_motor->retDir(), HIGH);
    start_time = time(NULL);
    while ((digitalRead(ES_Z) == false)) {
        end_time = time(NULL);
        if ((end_time - start_time) == 20) {
            // Failed
            sendSignal(INTERRUPT_CODE::AUTO_HOME_FAILED);
        } else {
            z_motor->rotateMotorInfinite(SPEED_MOTOR::SPEED_MID);
        }
    }
    coord->setZ(0);
    Timer::TIMER_Del();
}

void InnerFunction::FileTest() {
    ifstream file("/home/pi/project/C_xyzCalibration_cube.gcode");
    do {
        getline(file, test);
        cout << test << endl;
        if (test.at(0) == ';') {
            // Skip immediately
            continue;
        }
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
        } else if (first_bits == "G1" || first_bits == "G0") {
            static float speed = 0;
            float xmm = 0, ymm = 0, zmm = 0;
            if (seen('F')) {
                first_bits = first_bits.substr(1, test.find(" "));
                speed = stof(first_bits);
            }
            if (seen('X')) {
                first_bits = first_bits.substr(1, test.find(" "));
                xmm = stof(first_bits);
            }
            if (seen('Y')) {
                first_bits = first_bits.substr(1, test.find(" "));
                ymm = stof(first_bits);
            }
            if (seen('Z')) {
                first_bits = first_bits.substr(1, test.find(" "));
                zmm = stof(first_bits);
            }
            GCodeWrapper::G1(speed, xmm, ymm, zmm);
        } else if (first_bits == "MOUT") {
            break;
        } else {
            cout << "Unknown Command: \"" << test << "\"" << endl;
        }
    } while (!file.eof());
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
        } else if (first_bits == "G1" || first_bits == "G0") {
            static float speed = 0;
            float xmm = 0, ymm = 0, zmm = 0;
            if (seen('F')) {
                first_bits = first_bits.substr(1, test.find(" "));
                speed = stof(first_bits);
            }
            if (seen('X')) {
                first_bits = first_bits.substr(1, test.find(" "));
                xmm = stof(first_bits);
            }
            if (seen('Y')) {
                first_bits = first_bits.substr(1, test.find(" "));
                ymm = stof(first_bits);
            }
            if (seen('Z')) {
                first_bits = first_bits.substr(1, test.find(" "));
                zmm = stof(first_bits);
            }
            cout << "SPEED: " << speed << endl;
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