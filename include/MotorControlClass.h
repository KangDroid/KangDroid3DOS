class MotorControlClass : public PinClass {
    public:
        static void invertDirection();
        static void controlStepper();
        static void rotateMotor(int steps, int speed);
        static void rotateMotorInfinite(int speed);
        MotorControlClass();
};