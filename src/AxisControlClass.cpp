/**
 *  Calculate length and move the device
 */
#include "main.h"

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
        if(x_coord != -1) {
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
    z_motor.rotateMotor(length * STEPS_PER_MM::Z, SPEED_MOTOR::SPEED_LOW);
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