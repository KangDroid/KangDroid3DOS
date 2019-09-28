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
        static void moveTest(int tx, int ty);
        static void calculateMovements(int target_x, int target_y, int* stp_x, int* stp_y);
        static void moveTestY(int speed, int steps);
        static void moveTestX(int speed, int steps);
};