#include "main.h"

void EndstopClass::initPin() {
    for (int i = 0; i < ENDSTOP_PIN_COUNT; i++) {
        pinMode(es_pin[i], mode);
        pullUpDnControl(es_pin[i], pull_mode);
    }
}

EndstopClass::EndstopClass(int es_pin[], int mode, int pull_mode) {
    this->es_pin = new int[ENDSTOP_PIN_COUNT];
    for (int i = 0; i < ENDSTOP_PIN_COUNT; i++) {
        this->es_pin[i] = es_pin[i];
    }
    this->mode = mode;
    this->pull_mode = pull_mode;
}

EndstopClass::~EndstopClass() {
    delete this->es_pin;
}