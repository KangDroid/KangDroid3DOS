#include "main.h"

PinClass::PinClass(int x, int y, int z) { // The endstop constructor
    wiringPiSetup();

    // Endstop pinout
    pinMode(x, INPUT);
    pinMode(y, INPUT);
    pinMode(z, INPUT);
}

PinClass::PinClass(int step, int dir) { // The Motor Constructor
    wiringPiSetup();

    // Initiate motor
    if (step != -1 && dir != -1) {
        pinMode(step, OUTPUT);
        pinMode(dir, OUTPUT);
    }
}