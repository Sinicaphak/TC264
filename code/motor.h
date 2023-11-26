//ifdef
#ifndef _MOTOR_H_
#define _MOTOR_H_

// 电机最大值
#define MOTOR_MAX (3000)

extern double motor_input_l;
extern double motor_input_r;
void motor_move(double input_l, double input_r);
// endif
#endif




