#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include <cstring>

using namespace std;

static int pin_array[] = { /* Endstop Pinmap Array */
    7, /* X */
    0, /* Y */
    2, /* Z */
};

enum INTERRUPT_CODE {
    AUTO_HOME_FAILED = 0
};

const static int es_pin_count = sizeof(pin_array)/sizeof(int);

void initPinsGPIO();
int showMenu();
void getGCodeInput();
void sendSignal(int cause);
void clearScreen();
