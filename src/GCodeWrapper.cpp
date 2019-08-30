#include "main.h"

void GCodeWrapper::G28() {
    InnerFunction::autoHomeSimulation();
}

void GCodeWrapper::M119() {
    InnerFunction::testEndstopPin();
}

void GCodeWrapper::M18() {
    mcc.disableStepper();
}

void GCodeWrapper::G1(int feedrate, int x, int y, int z) {
    if (feedrate >= 0 && feedrate <= 500) {
        feedrate = SPEED_MOTOR::SPEED_LOW;
    } else if (feedrate > 500 && feedrate <= 1000) {
        feedrate = SPEED_MOTOR::SPEED_MID;
    } else if (feedrate > 1000 && feedrate <= 5000) {
        feedrate = SPEED_MOTOR::SPEED_HIGH;
    }
    mcc.rotateMotor(STEPS_PER_MM::Z * z, feedrate);
}