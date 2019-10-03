#include "main.h"

void EndstopClass::initPin() {
    pullUpDnControl(this->x, pull_mode);
    pullUpDnControl(this->y, pull_mode);
    pullUpDnControl(this->z, pull_mode);
}

void EndstopClass::currentStatus() {
    cout << "Current PIN Status:" << endl;
    cout << "X: " << ((digitalRead(this->x) == false) ? ": PROBED" : ": UNPROBED") << endl;
    cout << "Y: " << ((digitalRead(this->y) == false) ? ": PROBED" : ": UNPROBED") << endl;
    cout << "Z: " << ((digitalRead(this->z) == true) ? ": PROBED" : ": UNPROBED") << endl;
    cout << endl << endl;
}

EndstopClass::EndstopClass(int x, int y, int z, int pull_mode) : PinClass(x, y, z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->pull_mode = pull_mode;
    initPin();
}