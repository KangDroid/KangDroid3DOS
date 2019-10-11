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

// Initiate
Coord *coord = new Coord();
EndstopClass *es = new EndstopClass(ES_X, ES_Y, ES_Z, PUD_UP);
MotorControlClass *z_motor = new MotorControlClass(MOTOR_Z_STEP, MOTOR_Z_DIR, MOTOR_OFF);
MotorControlClass *x_motor = new MotorControlClass(MOTOR_X_STEP, MOTOR_X_DIR, MOTOR_OFF);
MotorControlClass *y_motor = new MotorControlClass(MOTOR_Y_STEP, MOTOR_Y_DIR, MOTOR_OFF);
MotorControlClass *e_motor = new MotorControlClass(-1, -1, MOTOR_OFF);
AxisControlClass *axis = new AxisControlClass(1);

int main(void) {
    int menu_val;
    /**
     * Basically, we need to check whether this program
     * is running on ROOT or not.
     * We are using direct-HW based Clock.
     */
    if (geteuid() != 0) {
        cout << "You are running this program as non-root." << endl;
        cout << "This program needs root prior to use HW Based clock." << endl;
        cout << "Abort." << endl;
        return 0;
    }

    // Implementation
    wiringPiSetup();
    es->initPin();

    do {
        menu_val = showMenu();
        switch(menu_val) {
            case 1:
                clearScreen();
                es->currentStatus();
            break;
            case 2:
                clearScreen();
                InnerFunction::autoHomeSimulation();
            break;
            case 3:
                clearScreen();
                InnerFunction::getGCodeInput();
            break;
            case 4:
                InnerFunction::FileTest();
            break;
        }
    } while(menu_val != 0);

    clearMemory();
    return 0;
}

void clearMemory() {
    delete coord;
    delete es;
    delete z_motor;
    delete x_motor;
    delete y_motor;
    delete e_motor;
    delete axis;
}

int showMenu() {
    int ret_val;

    cout << "1. Test Endstop PIN" << endl;
    cout << "2. Auto Home Simulation" << endl;
    cout << "3. Custom GCode terminal" << endl;
    cout << "4. Execute pre-defined test GCode file" << endl;
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