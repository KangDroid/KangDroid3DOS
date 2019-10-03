// Endstop Pins
#define ES_X 3
#define ES_Y 0
#define ES_Z 2


// Motor Pins
#define MOTOR_Y_DIR 30
#define MOTOR_Y_STEP 22
#define MOTOR_X_DIR 23
#define MOTOR_X_STEP 21
#define MOTOR_Z_DIR 4
#define MOTOR_Z_STEP 5
#define MOTOR_OFF 6

// Pin counter(For iteration)
#define ES_PIN_COUNT 3
#define MOTOR_PIN_COUNT 3

enum STEPS_PER_MM {
    X = 50,
    Y = 50,
    Z = 250,
    E = 1000,
};