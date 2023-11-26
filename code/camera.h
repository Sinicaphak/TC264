// ifndef
#ifndef _CAMERA_H_
#define _CAMERA_H_
//include
#include "zf_common_headfile.h"

extern int16 centerline[MT9V03X_H];
extern int16 leftline[MT9V03X_H];
extern int16 rightline[MT9V03X_H];
extern uint8 leftline_num;//���ߵ�����
extern uint8 rightline_num;//���ߵ�����
extern int16 SAR_THRE;//��Ⱥ���ֵ
extern uint8 PIX_PER_METER;//ÿ�׵�������

void image_boundary_process(void);
void difsum_right(uint8 y,uint8 x);
void difsum_left(uint8 y,uint8 x);
// endif
#endif