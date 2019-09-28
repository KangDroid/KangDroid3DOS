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