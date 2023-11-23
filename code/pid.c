#include "zf_common_headfile.h"

void active_p_pid(struct PositionalPid *pid, double err_now, struct Parameter *parameter){
    pid->err_now = err_now;
    pid->err_sum += err_now;

    pid->p_out = parameter->kp * pid->err_now;
    pid->i_out = parameter->ki * pid->err_sum;
    pid->d_out = parameter->kd * (pid->err_now - pid->err_last);

    pid->i_out = limit_amplitude_absolute(pid->i_out, parameter->i_max);
    pid->output = pid->p_out + pid->i_out + pid->d_out;
    pid->output = limit_amplitude_absolute(pid->output, parameter->out_max);

    pid->err_last = pid->err_now;
}

void active_i_pid(struct IncrementalPid *pid, double err_now, struct Parameter *parameter){
    pid->err_now = err_now;

    pid->p_out = parameter->kp * (pid->err_last - pid->err_last_last);
    pid->i_out = parameter->ki * pid->err_now;
    pid->d_out = parameter->kd * ( (pid->err_now - pid->err_last) - (pid->err_last - pid->err_last_last) );

    pid->i_out = limit_amplitude_absolute(pid->i_out, parameter->i_max);
    pid->output = pid->p_out + pid->i_out + pid->d_out;
    pid->output = limit_amplitude_absolute(pid->output, parameter->out_max);

    pid->err_last = pid->err_now;
    pid->err_last_last = pid->err_last;
  
}
