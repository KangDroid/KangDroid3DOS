/**
 *  Calculate length and move the device
 */
class AxisControlClass {
    private:
        int corexy = 0;
    public:
        AxisControlClass(int isCore);
        void moveX(int length);
        void moveY(int length);
        void moveZ(int length);
        void moveE(int length);
        static void *wrapperTesting(void *data);
        static void *wrapperTestingTwo(void *data);
};