#include "main.h"

MotorControlClass::MotorControlClass() {
    wiringPiSetup();
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(MOTOR_STEP, OUTPUT);
    pinMode(MOTOR_OFF, OUTPUT);
}

void MotorControlClass::invertDirection() {
    if (digitalRead(MOTOR_DIR) == 0) {
        digitalWrite(MOTOR_DIR, 1);
    } else {
        digitalWrite(MOTOR_DIR, 0);
    }
}

void MotorControlClass::enableStepper() {
    digitalWrite(MOTOR_OFF, HIGH);
    usleep(500000);
}
        
void MotorControlClass::disableStepper() {
    digitalWrite(MOTOR_OFF, LOW);
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