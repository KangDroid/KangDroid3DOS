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

#include <iostream>
#include <string>
#include <wiringPi.h>
#include <time.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <climits>
#include <fstream>

#include "PinClass.h"
#include "pins.h"
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include "MotorControlClass.h"
#include "AxisControlClass.h"
#include "timer.h"
#include "coord.h"

#define BCM2708_ST_BASE 0x3F003000 /* BCM 2835 System Timer */

using namespace std;

enum INTERRUPT_CODE {
    AUTO_HOME_FAILED = 0,
    SIG_OK = 1,
};

enum SPEED_MOTOR {
    SPEED_LOW = 32,
    SPEED_MID = 64,
    SPEED_HIGH = 128,
};

namespace AXIS {
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    const int E = 3;
}

int showMenu();
void getGCodeInput();
int sendSignal(int cause);
void clearScreen();
void clearMemory();

static string test;
static string first_bits;
static int pos;
static int machine_working;