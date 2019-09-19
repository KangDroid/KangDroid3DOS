/**
 *  Calculate length and move the device
 */
class AxisControlClass {
    private:
        int corexy = 0;
    public:
        AxisControlClass(int isCore);
        void moveX(int length, int speed);
        void moveY(int length, int speed);
        void moveZ(int length, int speed);
        void moveE(int length, int speed);
        void moveAxisInf(int speed);
        void moveTest();
        void calculateMovements(int target_x, int target_y, int* stp_x, int* stp_y);
};