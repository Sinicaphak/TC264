#include "zf_common_headfile.h"

void server_motor_move(double input){
    input = limit_amplitude_upper_lower(input, SERVER_DUTY_MAX, SERVER_DUTY_MIN);
    pwm_set_duty(SERVO_MOTOR_PWM, (uint32)input);
}