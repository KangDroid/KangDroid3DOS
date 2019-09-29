/**
 *  Calculate length and move the device
 */
#include "main.h"
#include "global.h"

void AxisControlClass::moveTestX(int speed, int steps) {
    for (int step_x = 0; step_x < steps; step_x++) {
        digitalWrite(x_motor->retStep(), HIGH);
        Timer::sleep_kangdroid(20800/speed);
        digitalWrite(x_motor->retStep(), LOW);
        Timer::sleep_kangdroid(20800/speed);
    }
}

void AxisControlClass::moveTestY(int speed, int steps) {
    for (int step_y = 0; step_y < steps; step_y++) {
        digitalWrite(y_motor->retStep(), HIGH);
        Timer::sleep_kangdroid(20800/speed);
        digitalWrite(y_motor->retStep(), LOW);
        Timer::sleep_kangdroid(20800/speed);
    } 
}

void AxisControlClass::moveTest(int target_xcoord, int target_ycoord) {
    /**
     * 1. Get current cooord
     * 2. Get Target Coord
     * 3. Calculate dx, dy
     * 4. Calculate STP(A), STP(B)
     * 5. Move it
     */
    int stp_x = 0, stp_y = 0, steps_cur = 0, run = 1, mul;
    int spd_x = 32, spd_y = 32;

    calculateMovements(target_xcoord, target_ycoord, &stp_x, &stp_y);
    cout << "STP_X: " << stp_x << endl;
    cout << "STP_Y: " << stp_y << endl;

    // Default to high
    digitalWrite(y_motor->retDir(), (stp_y >= 0) ? HIGH:LOW);
    stp_y = (stp_y < 0) ? -stp_y : stp_y;
    digitalWrite(x_motor->retDir(), (stp_x >= 0) ? HIGH:LOW);
    stp_x = (stp_x < 0) ? -stp_x : stp_x;
    cout << digitalRead(y_motor->retDir()) << endl;
    cout << digitalRead(x_motor->retDir()) << endl;
    

    // Calculate speed
    if (stp_x > stp_y) {
        mul = stp_x/stp_y;
        spd_y = spd_x / mul;
    } else {
        mul = stp_y/stp_x;
        spd_x = spd_y / mul;
    }

    // Initiate HW Clock and start thread.
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
    int dx = coord->retX() - target_x;
    int dy = coord->retY() - target_y;

    // Calculate STP
    *stp_x = STEPS_PER_MM::X * (dx + dy);
    *stp_y = STEPS_PER_MM::Y * (dy - dx);
}

void AxisControlClass::moveZ(int length, int speed) {
    int st_time, ed_time;
    st_time = time(NULL);
    z_motor->rotateMotor(length * STEPS_PER_MM::Z, SPEED_MOTOR::SPEED_LOW);
    ed_time = time(NULL);
    if (coord->retZ() != -1) {
        coord->setZ(length);
    }
}
void AxisControlClass::moveE(int length, int speed) {
    e_motor->rotateMotor(length * STEPS_PER_MM::E, SPEED_MOTOR::SPEED_LOW);
}

/**
 * Only for COREXY Devices
 */
void AxisControlClass::moveAxisInf(int speed) {
    digitalWrite(y_motor->retStep(), HIGH);
    usleep(20800/speed);
    digitalWrite(y_motor->retStep(), LOW);

    digitalWrite(x_motor->retStep(), HIGH);
    usleep(20800/speed);
    digitalWrite(x_motor->retStep(), LOW);
    usleep(20800/speed);
}

AxisControlClass::AxisControlClass(int isCore) {
    this->corexy = isCore;
}