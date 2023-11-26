#include "zf_common_headfile.h"
// 标志有无进入过中断
boolean has_break = false;
struct PositionalPid sm_pid;
struct Parameter sm_parameter = {
    .kp = 1e3,
    .ki = 0,
    .kd = 0,
    .i_max = 0,
    .out_max = 1000,
};
// 计算中线与屏幕中央竖线的偏差
double get_line_error(void){
    double output = 0;
    double temp = 0;
    // 寻迹线与竖线差值的和
    for (int i = 0; i < MT9V03X_H; i++){
        temp = trackline[i] - MT9V03X_W / 2;
        if (temp < 0){
            temp = -temp;
        }
        output += temp;
    }
    // 寻迹线斜率小于0, 输出负值
    if ( trackline[0] - trackline[MT9V03X_H - 1] < 0){
        output = -output;
    }
    return output;
}


void process_data(void){
    if (!has_break){
        return;
    }
    double server_input = get_line_error();
    active_p_pid(&sm_pid, server_input, &sm_parameter);

    motor_input_l = 2000;
    motor_input_r = 2000;
    server_motor_input =sm_pid.output;

    has_break = false;
}