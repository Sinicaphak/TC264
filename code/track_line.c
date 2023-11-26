#include "zf_common_headfile.h"
// ��־���޽�����ж�
boolean has_break = false;
struct PositionalPid sm_pid;
struct Parameter sm_parameter = {
    .kp = 1e3,
    .ki = 0,
    .kd = 0,
    .i_max = 0,
    .out_max = 1000,
};
// ������������Ļ�������ߵ�ƫ��
double get_line_error(void){
    double output = 0;
    double temp = 0;
    // Ѱ���������߲�ֵ�ĺ�
    for (int i = 0; i < MT9V03X_H; i++){
        temp = trackline[i] - MT9V03X_W / 2;
        if (temp < 0){
            temp = -temp;
        }
        output += temp;
    }
    // Ѱ����б��С��0, �����ֵ
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