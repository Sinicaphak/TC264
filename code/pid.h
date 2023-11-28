//ifdef
#ifndef _PID_H_
#define _PID_H_

// 位置式pid
struct PositionalPid {
    double err_now;
    double err_last;
    double err_sum;
    
    double p_out;
    double i_out;
    double d_out;

    double output;
};
// 增量式pid
struct IncrementalPid {
    double err_now;
    double err_last;
    double err_last_last;

    double p_out;
    double i_out;
    double d_out;

    double output;
};
struct Parameter {
    double kp;
    double ki;
    double kd;
    double i_max;
    double out_max;
};
// 位置式pid输出
void active_p_pid(struct PositionalPid *pid, double err_now, struct Parameter *parameter);
// 增量式pid输出
void active_i_pid(struct IncrementalPid *pid, double err_now, struct Parameter *parameter);

// endif
#endif
