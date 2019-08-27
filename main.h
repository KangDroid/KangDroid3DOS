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

const static int es_pin_count = sizeof(pin_array)/sizeof(int);

void initPinsGPIO();

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
static void clearScreen() {
    system("clear && printf '\e[3J'");
}
#endif