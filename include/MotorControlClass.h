class MotorControlClass : public PinClass {
    private:
        int step;
        int dir;
        int enable;
    public:
        void invertDirection();
        void enableStepper();
        void disableStepper();
        void rotateMotor(int steps, int speed);
        void rotateMotorInfinite(int speed);
        MotorControlClass(int step, int dir, int enable);
};