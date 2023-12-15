// ifndef
#ifndef _TRACK_LINE_H_
#define _TRACK_LINE_H_

#define ERROR_SHIFT 10
#define ERROR_SHIFT_GAIN 1

#define DEF_SPEED 25
#define ROUND_SPEED 15

extern double target_speed;
extern struct PositionalPid sm_pid;
extern struct Parameter sm_parameter;



void process_data(void);
// endif
#endif
