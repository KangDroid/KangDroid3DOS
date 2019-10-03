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
    axis->disableStepper();
    machine_working = sendSignal(INTERRUPT_CODE::SIG_OK);
}

void GCodeWrapper::G1(float feedrate, float x, float y, float z) {
    axis->enableStepper();
    Timer::TIMER_Init();
    if (x || y) {
        AxisControlClass::moveTest(x, y, (int)feedrate);
    }
    
    if (z) {
        AxisControlClass::moveZ(z, (int)feedrate);
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