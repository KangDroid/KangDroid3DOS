#include "main.h"

void GCodeWrapper::G28() {
    InnerFunction::autoHomeSimulation();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::M119() {
    es.currentStatus();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::M18() {
    z_motor.disableStepper();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::G1(int feedrate, int x, int y, int z) {
    if (feedrate >= 0 && feedrate <= 500) {
        feedrate = SPEED_MOTOR::SPEED_LOW;
    } else if (feedrate > 500 && feedrate <= 1000) {
        feedrate = SPEED_MOTOR::SPEED_MID;
    } else if (feedrate > 1000 && feedrate <= 5000) {
        feedrate = SPEED_MOTOR::SPEED_HIGH;
    }
    if (x) {
        axis.moveX(x, feedrate);
    }
    if (y) {
        axis.moveY(y, feedrate);
    }
    if (z) {
        axis.moveZ(z, feedrate);
    }
    //z_motor.rotateMotor(STEPS_PER_MM::Z * z, feedrate);
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}