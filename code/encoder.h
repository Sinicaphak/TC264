//ifdef
#ifndef _ENCODER_H_
#define _ENCODER_H_

#define REDUCTION_RATIO (1) // �������������ֵ�ת�ٱ�
#define PULSE_PER_CYCLE (1) // תһȦҪ���ٸ�����

extern int16 encoder_data_l;
extern int16 encoder_data_r ;
void read_encoder(void);
//endif
#endif