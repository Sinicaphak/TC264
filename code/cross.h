//ifndef
#ifndef _CROSS_H_
#define _CROSS_H_

#define CROSS_DIFF 10
enum CrossState {
    NO_CROSS = 0,
    SPOT_CROSS = 1,
    IN_CROSS = 2
};
extern enum CrossState cross_state;
extern int cross_out_j, cross_out_k, cross_out_l, cross_out_m;
void cross_track(void);

//endif
#endif