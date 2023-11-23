#include "zf_common_headfile.h"

void motor_move(double input_l, double input_r){
	
	input_l = limit_amplitude_absolute(input_l, MOTOR_MAX);
	input_r = limit_amplitude_absolute(input_r, MOTOR_MAX);

    if (IS_FULL_BRIDGE){
        // È«ÇÅ
        if (input_l < 0){
            input_l = -input_l;
            gpio_set_level(FULL_BRIDGE_LEFT_DIR, FULL_MOTOR_BACKWARD);
            pwm_set_duty(FULL_BRIDGE_LEFT_PWM, (uint32)input_l);
        }else{
            gpio_set_level(FULL_BRIDGE_LEFT_DIR, FULL_MOTOR_FORWARD);
            pwm_set_duty(FULL_BRIDGE_LEFT_PWM, (uint32)input_l);
        }

        if (input_r < 0){
            input_r = -input_r;
            gpio_set_level(FULL_BRIDGE_RIGHT_DIR, FULL_MOTOR_BACKWARD);
            pwm_set_duty(FULL_BRIDGE_RIGHT_PWM, (uint32)input_r);
        }else{
            gpio_set_level(FULL_BRIDGE_RIGHT_DIR, FULL_MOTOR_FORWARD);
            pwm_set_duty(FULL_BRIDGE_RIGHT_PWM, (uint32)input_r);
        }
    } else {
        // °ëÇÅ
        if (input_l < 0){
            input_l = -input_l;
            pwm_set_duty(HALF_BRIDGE_LEFT_B, (uint32)input_l);
            pwm_set_duty(HALF_BRIDGE_LEFT_A, 0);	
        }else{
            pwm_set_duty(HALF_BRIDGE_LEFT_B, 0);
            pwm_set_duty(HALF_BRIDGE_LEFT_A, (uint32)input_l);
        }
        
        if (input_r < 0){
            input_r = -input_r;
            pwm_set_duty(HALF_BRIDGE_RIGHT_B, (uint32)input_l);
            pwm_set_duty(HALF_BRIDGE_RIGHT_A, 0);	
        }else{
            pwm_set_duty(HALF_BRIDGE_RIGHT_B, 0);
            pwm_set_duty(HALF_BRIDGE_RIGHT_A, (uint32)input_l);
        }
    }
    
	

}