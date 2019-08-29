class MotorControlClass {
    public:
        static void invertDirection();
        static void enableStepper();
        static void disableStepper();
        static void rotateMotor(int steps, int speed);
        static void rotateMotorInfinite(int speed);
        MotorControlClass();
};