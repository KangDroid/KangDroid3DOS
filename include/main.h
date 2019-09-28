#include <iostream>
#include <string>
#include <wiringPi.h>
#include <time.h>
#include <unistd.h>
#include "PinClass.h"
#include "pins.h"
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include "MotorControlClass.h"
#include "AxisControlClass.h"
#include "timer.h"
#include "coord.h"
#include <cstring>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <climits>

#define BCM2708_ST_BASE 0x3F003000 /* BCM 2835 System Timer */

using namespace std;


static volatile unsigned *TIMER_registers;

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

static EndstopClass es(ES_X, ES_Y, ES_Z, PUD_UP);
static MotorControlClass z_motor(-1, -1, MOTOR_OFF);
static MotorControlClass x_motor(MOTOR_X_STEP, MOTOR_X_DIR, MOTOR_OFF);
static MotorControlClass y_motor(MOTOR_Y_STEP, MOTOR_Y_DIR, MOTOR_OFF);
static MotorControlClass e_motor(-1, -1, MOTOR_OFF);
static AxisControlClass axis(1);
static Coord coord;
static string test;
static string first_bits;
static int pos;
static int machine_working;