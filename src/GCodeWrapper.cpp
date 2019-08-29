#include "main.h"

void GCodeWrapper::G28() {
    InnerFunction::autoHomeSimulation();
}

void GCodeWrapper::M119() {
    InnerFunction::testEndstopPin();
}

void GCodeWrapper::M18() {
    mcc.disableStepper();
}