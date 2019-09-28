#include "main.h"
#include "global.h"

void GCodeWrapper::G28() {
    InnerFunction::autoHomeSimulation();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::M119() {
    es->currentStatus();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::M18() {
    z_motor->disableStepper();
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

    if (x || y) {
        AxisControlClass::moveTest(x, y);
    }
    if (z) {
        axis->moveZ(z, feedrate);
    }
    //z_motor.rotateMotor(STEPS_PER_MM::Z * z, feedrate);
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::M114() {
    InnerFunction::showInfoAxis();
}

/**
 * Coordnate function algorithm;
 * 1. When program initiated, each coordinates its states should be set to zero. 
 * 2. After homing procedure(Or each axis homing procedure), Each axis its coordinates should have set to something like 0;
 * 3. When motor moves
*/