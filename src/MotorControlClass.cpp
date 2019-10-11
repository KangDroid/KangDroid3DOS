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

void MotorControlClass::rotateMotor(int steps, int speed) {
    //enableStepper();
    for (int i = 0; i < steps; i++) {
        digitalWrite(this->step, HIGH);
        Timer::sleep_kangdroid(speed);
        digitalWrite(this->step, LOW);
        Timer::sleep_kangdroid(speed);
    }
}

void MotorControlClass::rotateMotorInfinite(int speed) {
    digitalWrite(this->step, HIGH);
    Timer::sleep_kangdroid(20800/speed);
    digitalWrite(this->step, LOW);
    Timer::sleep_kangdroid(20800/speed);
}

int MotorControlClass::retStep() {
    return this->step;
}
int MotorControlClass::retDir() {
    return this->dir;
}