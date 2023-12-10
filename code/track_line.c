#include "zf_common_headfile.h"

double target_speed = 100;
struct PositionalPid sm_pid, lm_pid, rm_pid;
struct Parameter sm_parameter = {
    .kp = 7.2e-2,
    .ki = 0,
    .kd = 5e-3,
    .i_max = 0,
    .out_max = SERVER_DUTY_MIDDLE - SERVER_DUTY_MIN,
};

struct Parameter lm_parameter = {
    .kp = 15,
    .ki = 0,
    .kd = 1e1,
    .i_max = 1200,
    .out_max = MOTOR_MAX,
};

struct Parameter rm_parameter = {
    .kp = 13,
    .ki = 0,
    .kd = 2e1,
    .i_max = 1200,
    .out_max = MOTOR_MAX,
};
// 计算中线与屏幕中央竖线的偏差
double get_line_error(void){
    static int16 his_trackpoint[2];
    double output = 0;
    double temp = 0;
    // 寻迹线与竖线差值的和
    for (int i = MT9V03X_H / 2; i < MT9V03X_H - 2; i++){
        // 将当前点与前后点做比较
        // his_trackpoint[0] = trackline[i - 1];
        // his_trackpoint[1] = trackline[i + 1];
        // temp = average(his_trackpoint, 2);
        // if (temp - trackline[i] < AVR_THS) {
        //     temp = trackline[i];
        // }
        temp = MT9V03X_H / 2 - trackline[i] + 32;
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
    
    round_track();
    double server_input = get_line_error();
    active_p_pid(&sm_pid, server_input - END_SHIFT, &sm_parameter);
    // 电机pid
    // active_p_pid(&lm_pid, target_speed - encoder_data_l, &lm_parameter);
    // active_p_pid(&rm_pid, target_speed - encoder_data_r, &rm_parameter);

    motor_input_l = 2300;
    motor_input_r = 2300;
    server_motor_input =sm_pid.output + SERVER_DUTY_MIDDLE;
}
