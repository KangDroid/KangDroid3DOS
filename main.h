#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "EndstopClass.h"
#include "GCodeWrapper.h"
#include "InnerFunction.h"
#include <cstring>

using namespace std;

#define ENDSTOP_PIN_COUNT 3

static int pin_array[] = { /* Endstop Pinmap Array */
    7, /* X */
    0, /* Y */
    2, /* Z */
};

void initPinsGPIO();

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
static void clearScreen() {
    system("clear && printf '\e[3J'");
}
#endif