//ifdef
#ifndef _PID_H_
#define _PID_H_

// λ��ʽpid
struct PositionalPid {
    double err_now;
    double err_last;
    double err_sum;
    
    double p_out;
    double i_out;
    double d_out;

    double output;
};
// ����ʽpid
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
// λ��ʽpid���
void active_p_pid(struct PositionalPid *pid, double err_now, struct Parameter *parameter);
// ����ʽpid���
void active_i_pid(struct IncrementalPid *pid, double err_now, struct Parameter *parameter);

// endif
#endif
