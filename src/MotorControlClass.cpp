#include "main.h"

MotorControlClass::MotorControlClass() {
    PinClass();
}

void MotorControlClass::invertDirection() {
    if (digitalRead(MOTOR_DIR) == 0) {
        digitalWrite(MOTOR_DIR, 1);
    } else {
        digitalWrite(MOTOR_DIR, 0);
    }
}

void MotorControlClass::enableStepper() {
    if (digitalRead(MOTOR_OFF) == LOW) {
        digitalWrite(MOTOR_OFF, HIGH);
    }
}

void MotorControlClass::disableStepper() {
    if (digitalRead(MOTOR_OFF) == HIGH) {
        digitalWrite(MOTOR_OFF, LOW);
    }
    usleep(500000);
}

void MotorControlClass::rotateMotor(int steps, int speed) {
    enableStepper();
    for (int i = 0; i < steps; i++) {
        digitalWrite(MOTOR_STEP, HIGH);
        usleep(20800/speed);
        digitalWrite(MOTOR_STEP, LOW);
        usleep(20800/speed);
    }
}

void MotorControlClass::rotateMotorInfinite(int speed) {
    digitalWrite(MOTOR_STEP, HIGH);
    usleep(20800/speed);
    digitalWrite(MOTOR_STEP, LOW);
    usleep(20800/speed);
}