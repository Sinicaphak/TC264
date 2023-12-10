//ifndef
#ifndef _ROUND_H_
#define _ROUND_H_

#define ROUND_BREAK_THS 6

#define LEFT_LINE_BOUNDARY 7
#define RIGHT_LINE_BOUNDARY MT9V03X_W - 5

// �󻷵�ƫ��
#define READY_IN_ROUND_SHIFT 2 // Ԥ�뻷ƫ��
#define IN_ROUND_SHIFT 5 // Ԥ�뻷ƫ��
#define OUT_ROUND_SHIFT 5 // ������ƫ��

enum ROUND_STATE {
    NO_ROUND = 0,
    READY_IN_ROUND = 1,
    IN_ROUND = 2,
    ROUNDING = 3,
    READY_OUT_ROUND = 4,
    OUT_ROUND = 5
};

extern enum ROUND_STATE round_state;

void round_track(    
    void
);

//endif
#endif
