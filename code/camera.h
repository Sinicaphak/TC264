// ifndef
#ifndef _CAMERA_H_
#define _CAMERA_H_
//include
#include "zf_common_headfile.h"

extern int16 centerline[MT9V03X_H];
extern int16 leftline[MT9V03X_H];
extern int16 rightline[MT9V03X_H];
extern uint8 leftline_num;//左线点数量
extern uint8 rightline_num;//右线点数量
extern int16 SAR_THRE;//差比和阈值
extern uint8 PIX_PER_METER;//每米的像素数

void image_boundary_process(void);
void difsum_right(uint8 y,uint8 x);
void difsum_left(uint8 y,uint8 x);
// endif
#endif