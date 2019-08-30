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
#include <cstring>

using namespace std;

enum INTERRUPT_CODE {
    AUTO_HOME_FAILED = 0
};

enum SPEED_MOTOR {
    SPEED_LOW = 32,
    SPEED_MID = 64,
    SPEED_HIGH = 128,
};

int showMenu();
void getGCodeInput();
void sendSignal(int cause);
void clearScreen();

static MotorControlClass mcc;
static string test;
static string first_bits;
static int pos;