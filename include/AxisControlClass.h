/**
 *  Calculate length and move the device
 */
class AxisControlClass {
    private:
        int corexy = 0;
    public:
        AxisControlClass(int isCore);
        void moveZ(int length, int speed);
        void moveE(int length, int speed);
        void moveAxisInf(int speed);
        static void calculateSpeed(int &speed_x, int &speed_y, const int &fr, int &target_feedrate);
        static int roundUP(float input);
        static void moveTest(float target_xcoord, float target_ycoord, int target_fr);
        static void calculateMovements(float target_x, float target_y, int* stp_x, int* stp_y);
        static void moveTestY(int speed, int steps);
        static void moveTestX(int speed, int steps);
};