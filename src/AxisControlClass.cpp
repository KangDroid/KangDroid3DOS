/**
 *  Calculate length and move the device
 */
#include "main.h"

void AxisControlClass::moveTestX(int speed, int steps) {
    //cout << "X Working" << endl;
    for (int step_x = 0; step_x < steps; step_x++) {
        digitalWrite(x_motor.retStep(), HIGH);
        Timer::sleep_kangdroid(20800/speed);
        digitalWrite(x_motor.retStep(), LOW);
        Timer::sleep_kangdroid(20800/speed);
        //cout << "X Working" << endl;
    } 
    cout << "X Finished" << endl;
}

void AxisControlClass::moveTestY(int speed, int steps) {
    for (int step_y = 0; step_y < steps; step_y++) {
        digitalWrite(y_motor.retStep(), HIGH);
        Timer::sleep_kangdroid(20800/speed);
        digitalWrite(y_motor.retStep(), LOW);
        Timer::sleep_kangdroid(20800/speed);
        //cout << "Y Working" << endl;
    } 
    cout << "Y Finished" << endl;
}

void AxisControlClass::moveTest() {
    /**
     * 1. Get current cooord
     * 2. Get Target Coord
     * 3. Calculate dx, dy
     * 4. Calculate STP(A), STP(B)
     * 5. Move it
     */
    int stp_x = 0, stp_y = 0, steps_cur = 0, run = 1, mul;
    int spd_x = 32, spd_y = 32;
    calculateMovements(10, 20, &stp_x, &stp_y);
    cout << "STP_X: " << stp_x << endl;
    cout << "STP_Y: " << stp_y << endl;

    // Default to high
    digitalWrite(y_motor.retDir(), (stp_y >= 0) ? HIGH:LOW);
    stp_x = (stp_x < 0) ? -stp_x : stp_x;
    digitalWrite(x_motor.retDir(), (stp_x >= 0) ? HIGH:LOW);
    stp_y = (stp_y < 0) ? -stp_y : stp_y;

    if (stp_x > stp_y) {
        mul = stp_x/stp_y;
        spd_y = spd_x / mul;
        cout << "SPEED OF Y: " << spd_y << endl;
    } else {
        mul = stp_y/stp_x;
        spd_x = spd_y / mul;
        cout << "SPEED OF X: " << spd_x << endl; 
    }
    Timer::TIMER_Init();
    thread tx(moveTestX, spd_x, stp_x);
    thread ty(moveTestY, spd_y, stp_y);

    /**
     * Use join or detach.
     */
    tx.join();
    ty.join();
}

void AxisControlClass::calculateMovements(int target_x, int target_y, int* stp_x, int* stp_y) {
    // Calculate dx, dy
    int dx = x_coord - target_x;
    int dy = y_coord - target_y;

    // Calculate STP
    *stp_x = STEPS_PER_MM::X * (dx + dy);
    *stp_y = STEPS_PER_MM::Y * (dy - dx);
}

void AxisControlClass::moveX(int length, int speed) {
    if (corexy) {
        if (x_coord != -1) {
            digitalWrite(y_motor.retDir(), (x_coord < length) ? HIGH:LOW);
            digitalWrite(x_motor.retDir(), (x_coord < length) ? LOW:HIGH);
            x_coord = length;
        } else if (x_coord == -1) {
            //positive
            digitalWrite(y_motor.retDir(), HIGH);
            digitalWrite(x_motor.retDir(), LOW);
        }
        for (int i = 0; i < STEPS_PER_MM::X * length; i++) { // TODO: Motor naming
            this->moveAxisInf(speed);
        }
    } else {
        // NORMAL Printer mechanism like Anet, ETC(NOT SF)
        if (x_coord != -1) {
            digitalWrite(x_motor.retDir(), (x_coord < length) ? LOW:HIGH);
            x_coord = length;
        } else if (x_coord == -1) {
            digitalWrite(x_motor.retDir(), HIGH);
        }
        x_motor.rotateMotor(length * STEPS_PER_MM::X, speed);
    }
}
void AxisControlClass::moveY(int length, int speed) {
    if (corexy) {
        if (y_coord != -1) {
            digitalWrite(y_motor.retDir(), (y_coord < length) ? HIGH:LOW);
            digitalWrite(x_motor.retDir(), (y_coord < length) ? HIGH:LOW);
            y_coord = length;
        } else if (y_coord == -1) {
            //positive
            digitalWrite(y_motor.retDir(), HIGH);
            digitalWrite(x_motor.retDir(), HIGH);
        }
        for (int i = 0; i < STEPS_PER_MM::Y * length; i++) { // TODO: Motor naming
            this->moveAxisInf(speed);
        }
    } else {
        // NORMAL Printer mechanism like Anet, ETC(NOT SF)
        if (y_coord != -1) {
            digitalWrite(y_motor.retDir(), (y_coord < length) ? LOW:HIGH);
            y_coord = length;
        } else if (y_coord == -1) {
            digitalWrite(y_motor.retDir(), HIGH);
        }
        y_motor.rotateMotor(length * STEPS_PER_MM::Y, speed);
    }
}
void AxisControlClass::moveZ(int length, int speed) {
    int st_time, ed_time;
    st_time = time(NULL);
    z_motor.rotateMotor(length * STEPS_PER_MM::Z, SPEED_MOTOR::SPEED_LOW);
    ed_time = time(NULL);
    cout << "TIME: " << ed_time - st_time << endl;
    if (z_coord != -1) {
        z_coord = length;
    }
}
void AxisControlClass::moveE(int length, int speed) {
    e_motor.rotateMotor(length * STEPS_PER_MM::E, SPEED_MOTOR::SPEED_LOW);
}

/**
 * Only for COREXY Devices
 */
void AxisControlClass::moveAxisInf(int speed) {
    digitalWrite(y_motor.retStep(), HIGH);
    usleep(20800/speed);
    digitalWrite(y_motor.retStep(), LOW);

    digitalWrite(x_motor.retStep(), HIGH);
    usleep(20800/speed);
    digitalWrite(x_motor.retStep(), LOW);
    usleep(20800/speed);
}

AxisControlClass::AxisControlClass(int isCore) {
    this->corexy = isCore;
}