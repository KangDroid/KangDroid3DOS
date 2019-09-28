#include "main.h"

MotorControlClass::MotorControlClass(int step, int dir, int enable) : PinClass(step, dir) {
    pinMode(enable, OUTPUT);

    if (step != -1 && dir != -1) {
        this->step = step;
        this->dir = dir;
    }
    this->enable = enable;
}

void MotorControlClass::invertDirection() {
    if (digitalRead(this->dir) == 0) {
        digitalWrite(this->dir, 1);
    } else {
        digitalWrite(this->dir, 0);
    }
}

void MotorControlClass::enableStepper() {
    if (digitalRead(this->enable) == LOW) {
        digitalWrite(this->enable, HIGH);
    }
}

void MotorControlClass::disableStepper() {
    if (digitalRead(this->enable) == HIGH) {
        digitalWrite(this->enable, LOW);
    }
    coord.setX(-1);
    coord.setY(-1);
    coord.setZ(-1);
    usleep(500000);
}

void MotorControlClass::rotateMotor(int steps, int speed) {
    //enableStepper();
    for (int i = 0; i < steps; i++) {
        digitalWrite(this->step, HIGH);
        usleep(20800/speed);
        digitalWrite(this->step, LOW);
        usleep(20800/speed);
    }
}

void MotorControlClass::rotateMotorInfinite(int speed) {
    digitalWrite(this->step, HIGH);
    usleep(20800/speed);
    digitalWrite(this->step, LOW);
    usleep(20800/speed);
}

int MotorControlClass::retStep() {
    return this->step;
}
int MotorControlClass::retDir() {
    return this->dir;
}