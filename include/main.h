#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include "MotorControlClass.h"
#include <cstring>

using namespace std;

static int pin_es_array[] = { /* Endstop Pinmap Array */
    7, /* X */
    0, /* Y */
    2, /* Z */
};

#define MOTOR_DIR 25
#define MOTOR_STEP 24
#define MOTOR_OFF 27

enum INTERRUPT_CODE {
    AUTO_HOME_FAILED = 0
};

enum SPEED_MOTOR {
    SPEED_LOW = 32,
    SPEED_MID = 64,
    SPEED_HIGH = 128,
};

const static int es_pin_count = 3;
const static int motor_pin_count = 3;

int showMenu();
void getGCodeInput();
void sendSignal(int cause);
void clearScreen();

static MotorControlClass mcc;