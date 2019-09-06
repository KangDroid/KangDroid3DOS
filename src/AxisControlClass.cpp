/**
 *  Calculate length and move the device
 */
#include "main.h"
struct data_testing {
    int length;
    int speed;
} dataTesting;
void AxisControlClass::moveX(int length) {
    if (corexy) {
        digitalWrite(x_motor.retDir(), HIGH);
        digitalWrite(z_motor.retDir(), HIGH);
        dataTesting.length = length * STEPS_PER_MM::X;
        dataTesting.speed = SPEED_MOTOR::SPEED_LOW;
        pthread_t x_thread, y_thread;
        pthread_create(&x_thread, NULL, wrapperTesting, (void*)&dataTesting);
        pthread_create(&y_thread, NULL, wrapperTestingTwo, (void*)&dataTesting);
    } else {
        x_motor.rotateMotor(length * STEPS_PER_MM::X, SPEED_MOTOR::SPEED_LOW);
    }
}
void * AxisControlClass::wrapperTesting(void *data) {
    struct data_testing *data_ptr = (struct data_testing*) data;
    x_motor.rotateMotor(data_ptr->length, data_ptr->speed);
}
void * AxisControlClass::wrapperTestingTwo(void *data) {
    struct data_testing *data_ptr = (struct data_testing*) data;
    z_motor.rotateMotor(data_ptr->length, data_ptr->speed);
}
void AxisControlClass::moveY(int length) {
    if (corexy) {
    } else {
        y_motor.rotateMotor(length * STEPS_PER_MM::Y, SPEED_MOTOR::SPEED_LOW);
    }
}
void AxisControlClass::moveZ(int length) {
    z_motor.rotateMotor(length * STEPS_PER_MM::Z, SPEED_MOTOR::SPEED_LOW);
}
void AxisControlClass::moveE(int length) {
    e_motor.rotateMotor(length * STEPS_PER_MM::E, SPEED_MOTOR::SPEED_LOW);
}
AxisControlClass::AxisControlClass(int isCore) {
    this->corexy = isCore;
}