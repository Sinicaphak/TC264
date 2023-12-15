//ifndef
#ifndef _ROUND_H_
#define _ROUND_H_

//
#define LEFT_LINE_BOUNDARY 5
#define RIGHT_LINE_BOUNDARY MT9V03X_W - LEFT_LINE_BOUNDARY
//
#define BUTTON MT9V03X_H - 1
// �󻷵�ƫ��
#define BEFORE_ROUND_SHIFT 0-10
#define MID_ROUND_SHIFT 0-15 // Ԥ�뻷ƫ��
#define IN_ROUND_SHIFT 0-5 // �뻷ƫ��
#define OUT_ROUND_SHIFT 0-40 // ������ƫ��

enum ROUND_STATE {
    NO_ROUND = 0,
    PRE_IN_ROUND = 1,
    BEFORE_ROUND = 2,
    MID_ROUND = 3,
    READY_IN_ROUND = 4,
    IN_ROUND = 5,
    ROUNDING = 6,
    READY_OUT_ROUND = 7,
    OUT_ROUND = 8,
    ROUND_END = 9
};

extern enum ROUND_STATE round_state;
extern boolean right_s;
extern int out_j, out_k, out_rs;

void round_track(    
    void
);

//endif
#endif
