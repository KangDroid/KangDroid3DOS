#include <iostream>
#include <string>
#include <wiringPi.h>
#include <unistd.h>
#include "PinClass.h"
#include "pins.h"
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include "MotorControlClass.h"
#include "AxisControlClass.h"
#include <cstring>
#include <pthread.h>

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

static EndstopClass es(ES_X, ES_Y, ES_Z, PUD_UP);
static MotorControlClass z_motor(-1, -1, MOTOR_OFF);
static MotorControlClass x_motor(MOTOR_X_STEP, MOTOR_X_DIR, MOTOR_OFF);
static MotorControlClass y_motor(MOTOR_Y_STEP, MOTOR_Y_DIR, MOTOR_OFF);
static MotorControlClass e_motor(-1, -1, MOTOR_OFF);
static AxisControlClass axis(1);
static string test;
static string first_bits;
static int pos;
static int machine_working;
static int x_coord = -1, y_coord = -1, z_coord = -1;