// ifndef
#ifndef _TRACK_LINE_H_
#define _TRACK_LINE_H_

#define END_SHIFT 0
#define ERROR_SHIFT 10
#define ERROR_SHIFT_GAIN 1
#define AVR_THS 15
extern double target_speed;
extern struct PositionalPid sm_pid;
extern struct Parameter sm_parameter;



void process_data(void);
// endif
#endif
