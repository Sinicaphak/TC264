#include "zf_common_headfile.h"


// 计算中线与屏幕中央竖线的偏差
double get_line_error(void){
    double output = 0;
    double temp = 0;
    // 寻迹线与竖线差值的和
    for (int i = MT9V03X_H / 2; i < MT9V03X_H - 2; i++){
        temp = MT9V03X_W / 2 - trackline[i] + 0;
        // if (
        //     ( i < (MT9V03X_H - 2 - ERROR_SHIFT) ) && 
        //     ( i > (MT9V03X_H / 2 + ERROR_SHIFT) )
        // ) {
        //     temp *= ERROR_SHIFT_GAIN;
        // }
        output += temp;
    }
    return output;
}


void process_data(void){
    double server_input;
//    round_track();
    cross_track();

    server_input = get_line_error();
    active_p_pid(&sm_pid, server_input, &sm_parameter);
    server_motor_input = sm_pid.output + SERVER_DUTY_MIDDLE;
    server_motor_move(server_motor_input);
}
