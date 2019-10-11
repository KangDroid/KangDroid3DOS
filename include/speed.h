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

/**
 * Basic motor movement constant variables
 * DO NOT CHANGE
 */
#define MOTOR_SPEED_BASERATE 60
#define DEFAULT_MOTOR_SPEED 10000

/**
 * All unit is US(Micro-second)
 * MOTOR_SPEED_MAX_LIMIT will limit the speed of motor to 100us when linear-move.
 * JERK_SPEED_LIMIT will limit speed of motor to 2000us when diagonal movements OR
 * arc move. 
 * 
 * adding us-time will slow down the motor speed, substituting us-time will move motor
 * more faster.
 */
#define MOTOR_SPEED_MAX_LIMIT 100
#define JERK_SPEED_LIMIT 1000