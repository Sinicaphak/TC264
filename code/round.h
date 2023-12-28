//ifndef
#ifndef _ROUND_H_
#define _ROUND_H_

//
#define LEFT_LINE_BOUNDARY 5
#define RIGHT_LINE_BOUNDARY MT9V03X_W - LEFT_LINE_BOUNDARY
//
#define BUTTON MT9V03X_H - 1
// 〜┏?，??????
#define L_BEFORE_ROUND_SHIFT 0
#define L_MID_ROUND_SHIFT 5
#define L_IN_ROUND_SHIFT 0-5 // ???，????
#define L_OUT_ROUND_SHIFT 0-40 // ???，??????
// ???，??????
#define R_BEFORE_ROUND_SHIFT 10
#define R_MID_ROUND_SHIFT 15
#define R_IN_ROUND_SHIFT 5 // ???，????
#define R_OUT_ROUND_SHIFT 40 // ???，??????

enum ROUND_DIR {
    NO_DIR = 0,
    LEFT_DIR = 1,
    RIGHT_DIR = 2,
    LOSS_DIR = 3
};

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
extern enum ROUND_DIR round_dir;
extern boolean right_s;
extern int out_j, out_k, out_rs;
extern int out_hrl, out_hrr;

void round_track(    
    void
);

//endif
#endif
