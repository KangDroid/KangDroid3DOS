/**
 * Copyright (C) 2019, Jason HW Kang(Aka. KangDroid, Hyun Woo Kang)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * If any violation of this project found, please contact to kangdroid@konkuk.ac.kr
 */

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