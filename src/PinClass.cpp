#include "main.h"

PinClass::PinClass() {
    wiringPiSetup();
    // Motor pinout
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(MOTOR_STEP, OUTPUT);
    pinMode(MOTOR_OFF, OUTPUT);

    // Endstop pinout
    pinMode(ES_X, INPUT);
    pinMode(ES_Y, INPUT);
    pinMode(ES_Z, INPUT);
}