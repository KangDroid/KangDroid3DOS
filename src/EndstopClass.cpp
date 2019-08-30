#include "main.h"

void EndstopClass::initPin() {
    pullUpDnControl(ES_X, pull_mode);
    pullUpDnControl(ES_Y, pull_mode);
    pullUpDnControl(ES_Z, pull_mode);
}

EndstopClass::EndstopClass(int pull_mode) {
    PinClass();
    this->pull_mode = pull_mode;
}