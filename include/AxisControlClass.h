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

/**
 *  Calculate length and move the device
 */
class AxisControlClass {
    private:
        int corexy = 0;
    public:
        AxisControlClass(int isCore);
        static void moveZ(float target_z, int target_fr);
        void moveE(int length, int speed);
        void moveAxisInf(int speed);
        void enableStepper();
        void disableStepper();
        static void calculateMovementsZ(float target_z, int &stp_z);
        static void calculateSpeed(int &speed_x, int &speed_y, const int &fr, int &target_feedrate);
        static void calculateSpeed(int &speed_z, const int &fr, int &target_feedrate);
        static int roundUP(float input);
        static void moveTest(float target_xcoord, float target_ycoord, int target_fr);
        static void calculateMovements(float target_x, float target_y, int* stp_x, int* stp_y);
        static void moveTestY(int speed, int steps);
        static void moveTestX(int speed, int steps);
};