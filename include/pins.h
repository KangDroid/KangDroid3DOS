// Endstop Pins
#define ES_X 7
#define ES_Y 0
#define ES_Z 2


// Motor Pins
#define MOTOR_Y_DIR 30
#define MOTOR_Y_STEP 22
#define MOTOR_X_DIR 23
#define MOTOR_X_STEP 21
#define MOTOR_OFF 27

// Pin counter(For iteration)
#define ES_PIN_COUNT 3
#define MOTOR_PIN_COUNT 3

enum STEPS_PER_MM {
    X = 200,
    Y = 200,
    Z = 1000,
    E = 1000,
};