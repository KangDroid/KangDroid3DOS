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

// Endstop Pins
#define ES_X 3
#define ES_Y 0
#define ES_Z 2


// Motor Pins
#define MOTOR_Y_DIR 30
#define MOTOR_Y_STEP 22
#define MOTOR_X_DIR 23
#define MOTOR_X_STEP 21
#define MOTOR_Z_DIR 4
#define MOTOR_Z_STEP 5
#define MOTOR_OFF 6

// Pin counter(For iteration)
#define ES_PIN_COUNT 3
#define MOTOR_PIN_COUNT 3

enum STEPS_PER_MM {
    X = 50,
    Y = 50,
    Z = 250,
    E = 1000,
};