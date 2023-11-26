//ifdef
#ifndef _ENCODER_H_
#define _ENCODER_H_

#define REDUCTION_RATIO (1) // 编码器与电机齿轮的转速比
#define PULSE_PER_CYCLE (1) // 转一圈要多少个脉冲

extern int16 encoder_data_l;
extern int16 encoder_data_r ;
void read_encoder(void);
//endif
#endif