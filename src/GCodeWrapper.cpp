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

void GCodeWrapper::G1() {
    mcc.rotateMotor(STEPS_PER_MM::Z * 10, SPEED_MOTOR::SPEED_MID);
}