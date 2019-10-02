/**
 * Basic motor movement constant variables
 * DO NOT CHANGE
 */
#define MOTOR_SPEED_BASERATE 60
#define DEFAULT_MOTOR_SPEED 10000

/**
 * All unit is US(Micro-second)
 * MOTOR_SPEED_MAX_LIMIT will limit the speed of motor to 100us when linear-move.
 * JERK_SPEED_LIMIT will limit speed of motor to 2000us when diagonal movements OR
 * arc move. 
 * 
 * adding us-time will slow down the motor speed, substituting us-time will move motor
 * more faster.
 */
#define MOTOR_SPEED_MAX_LIMIT 100
#define JERK_SPEED_LIMIT 2000