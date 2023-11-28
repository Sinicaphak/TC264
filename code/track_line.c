#include "zf_common_headfile.h"

double target_speed = 300;
struct PositionalPid sm_pid;
struct Parameter sm_parameter = {
    .kp = 7.0e-2,
    .ki = 0,
    .kd = 0,
    .i_max = 0,
    .out_max = 80,
};
// 计算中线与屏幕中央竖线的偏差
double get_line_error(void){
    double output = 0;
    double temp = 0;
    // 寻迹线与竖线差值的和
    for (int i = MT9V03X_H / 2; i < MT9V03X_H - 2; i++){
        temp = MT9V03X_W / 2 - trackline[i] ;
        if (
            ( i < (MT9V03X_H - 2 - ERROR_SHIFT) ) && 
            ( i > (MT9V03X_H / 2 + ERROR_SHIFT) )
        ) {
            temp *= ERROR_SHIFT_GAIN;
        }
        output += temp;
    }
    return output;
}


void process_data(void){
    double server_input = get_line_error();
    active_p_pid(&sm_pid, server_input, &sm_parameter);

    motor_input_l = 1300;
    motor_input_r = 1300;
    server_motor_input =sm_pid.output + SERVER_DUTY_MIDDLE + END_SHIFT;
}
