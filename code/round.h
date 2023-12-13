//ifndef
#ifndef _ROUND_H_
#define _ROUND_H_

#define ROUND_BREAK_THS 6
//
#define LEFT_LINE_BOUNDARY 7
#define RIGHT_LINE_BOUNDARY MT9V03X_W - 5
//
#define BUTTON MT9V03X_H - 1
// ×ó»·µºÆ«ÒÆ
#define READY_IN_ROUND_SHIFT 2 // Ô¤Èë»·Æ«ÒÆ
#define IN_ROUND_SHIFT 5 // Ô¤Èë»·Æ«ÒÆ
#define OUT_ROUND_SHIFT 5 // ³ö»·µºÆ«ÒÆ

enum ROUND_STATE {
    NO_ROUND = 0,
    PRE_IN_ROUND = 1,
    READY_IN_ROUND = 2,
    IN_ROUND = 3,
    ROUNDING = 4,
    READY_OUT_ROUND = 5,
    OUT_ROUND = 6
};

extern enum ROUND_STATE round_state;
extern boolean right_s;
extern int out_j, out_k, out_z;

void round_track(    
    void
);

//endif
#endif
