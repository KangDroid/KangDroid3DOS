/**
 * Copyright (C) 2019, Jason HW Kang(Aka. KangDroid, Hyun Woo Kang)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * If any violation of this project found, please contact to kangdroid@konkuk.ac.kr
 */

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
    Timer::TIMER_Del(); // Free those Timer;
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