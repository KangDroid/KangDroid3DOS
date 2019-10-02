/**
 *  Calculate length and move the device
 */
#include "main.h"
#include "global.h"
#include "speed.h"

void AxisControlClass::moveTestX(int speed, int steps) {
    for (int step_x = 0; step_x < steps; step_x++) {
        digitalWrite(x_motor->retStep(), HIGH);
        Timer::sleep_kangdroid(speed);
        digitalWrite(x_motor->retStep(), LOW);
        Timer::sleep_kangdroid(speed);
    }
}

void AxisControlClass::moveTestY(int speed, int steps) {
    for (int step_y = 0; step_y < steps; step_y++) {
        digitalWrite(y_motor->retStep(), HIGH);
        Timer::sleep_kangdroid(speed);
        digitalWrite(y_motor->retStep(), LOW);
        Timer::sleep_kangdroid(speed);
    } 
}

int AxisControlClass::roundUP(float input) {
    if ((input - (int)input) < 0.5) {
        return (int)input;
    } else {
        return (int)(input + 0.5);
    }
}

void AxisControlClass::calculateSpeed(int &speed_x, int &speed_y, const int &fr, int &target_feedrate) {
    float spd_tmpx;
    if (target_feedrate > fr) {
        spd_tmpx = ((float)target_feedrate / fr);
        spd_tmpx = (speed_x / spd_tmpx);
        speed_x = roundUP(spd_tmpx);
        speed_y = roundUP(spd_tmpx);
    } else {
        spd_tmpx = (fr / (float)target_feedrate);
        spd_tmpx = (speed_x * spd_tmpx);
        speed_x = roundUP(spd_tmpx);
        speed_y = roundUP(spd_tmpx);
    }
}

void AxisControlClass::moveTest(float target_xcoord, float target_ycoord, int target_fr) {
    /**
     * 1. Get current cooord
     * 2. Get Target Coord
     * 3. Calculate dx, dy
     * 4. Calculate STP(A), STP(B)
     * 5. Move it
     */
    int stp_x = 0, stp_y = 0, steps_cur = 0, run = 1, mul;
    int spd_x = DEFAULT_MOTOR_SPEED;
    int spd_y = DEFAULT_MOTOR_SPEED;
    if (target_fr > 800) {
        target_fr = 800;
    }
    calculateSpeed(spd_x, spd_y, MOTOR_SPEED_BASERATE, target_fr);
    calculateMovements(target_xcoord, target_ycoord, &stp_x, &stp_y);

    // Default to high
    digitalWrite(y_motor->retDir(), (stp_y >= 0) ? HIGH:LOW);
    stp_y = (stp_y < 0) ? -stp_y : stp_y;
    digitalWrite(x_motor->retDir(), (stp_x >= 0) ? HIGH:LOW);
    stp_x = (stp_x < 0) ? -stp_x : stp_x;

    // Calculate speed
    if(stp_x != 0 && stp_y != 0) {
        if (stp_x > stp_y) {
            mul = stp_x/stp_y;
            spd_x = spd_y / mul;
        } else if (stp_x < stp_y) {
            mul = stp_y/stp_x;
            spd_y = spd_x / mul;
        }
    }

    /**
     * Limit PWM Rate to MOTOR_SPEED_MAX_LIMIT(100us) when moving normal linear movement
     * Limit PWM Rate to JERK_SPEED_LIMIT(2000us) when moving normal linear movement
     * TODO: Optimize those nasty-lazy code.
     */
    if (stp_x < 50 && stp_y < 50) {
        if (stp_x > stp_y) { // x has to be fast, y has to be slow.
            int tmp_mul = stp_x/stp_y;
            spd_x = JERK_SPEED_LIMIT;
            spd_y = JERK_SPEED_LIMIT * mul;
        } else if (stp_x < stp_y) {
            int tmp_mul = stp_y/stp_x;
            spd_y = JERK_SPEED_LIMIT;
            spd_x = JERK_SPEED_LIMIT * mul;
        } else {
            spd_y = JERK_SPEED_LIMIT;
            spd_x = JERK_SPEED_LIMIT;
        }
    } else {
        if (spd_x < MOTOR_SPEED_MAX_LIMIT || spd_y < MOTOR_SPEED_MAX_LIMIT) {
            if (spd_x < MOTOR_SPEED_MAX_LIMIT && spd_y < MOTOR_SPEED_MAX_LIMIT) {
                if (spd_x == spd_y) {
                    spd_x = MOTOR_SPEED_MAX_LIMIT;
                    spd_y = MOTOR_SPEED_MAX_LIMIT;
                } else {
                    // Get Multiplier
                    if (stp_x > stp_y) { // x has to be fast, y has to be slow.
                        int tmp_mul = stp_x/stp_y;
                        spd_x = MOTOR_SPEED_MAX_LIMIT;
                        spd_y = MOTOR_SPEED_MAX_LIMIT * mul;
                    } else {
                        int tmp_mul = stp_y/stp_x;
                        spd_y = MOTOR_SPEED_MAX_LIMIT;
                        spd_x = MOTOR_SPEED_MAX_LIMIT * mul;
                    }
                }
            } else if (spd_x < MOTOR_SPEED_MAX_LIMIT) {
                int tmp = MOTOR_SPEED_MAX_LIMIT - spd_x;
                spd_x += tmp; // make spd_x as 750;
                spd_y = spd_x * mul;
            } else if (spd_y < MOTOR_SPEED_MAX_LIMIT) {
                int tmp = MOTOR_SPEED_MAX_LIMIT - spd_y;
                spd_y += tmp; // make spd_x as MOTOR_SPEED_MAX_LIMIT;
                spd_x = spd_y * mul;      
            }
        }
    }

    coord->setX(target_xcoord);
    coord->setY(target_ycoord);

    // Initiate HW Clock and start thread.
    Timer::TIMER_Init();
    unsigned int st_time = Timer::TIMER_GetSysTick();
    thread tx(moveTestX, spd_x, stp_x);
    thread ty(moveTestY, spd_y, stp_y);

    /**
     * Use join or detach.
     */
    tx.join();
    ty.join();
    unsigned int ed_time = Timer::TIMER_GetSysTick();
    cout << "Execution of GCode took: " << ed_time - st_time << endl;
}

void AxisControlClass::calculateMovements(float target_x, float target_y, int* stp_x, int* stp_y) {
    // Calculate dx, dy
    float dx = coord->retX() - target_x;
    float dy = coord->retY() - target_y;

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
    Timer::sleep_kangdroid(20800/speed);
    digitalWrite(y_motor->retStep(), LOW);

    digitalWrite(x_motor->retStep(), HIGH);
    Timer::sleep_kangdroid(20800/speed);
    digitalWrite(x_motor->retStep(), LOW);
    Timer::sleep_kangdroid(20800/speed);
}

AxisControlClass::AxisControlClass(int isCore) {
    this->corexy = isCore;
}
