#include "zf_common_headfile.h"

enum CrossState cross_state = NO_CROSS;

int l_begin_y = 0, r_begin_y = 0, l_end_y = 0, r_end_y = 0;
int cross_out_j = 0, cross_out_k = 0, cross_out_l = 0, cross_out_m = 0;

void cross_check(void) {
    int i = BUTTON, j = 0, k = 0, l = 0, m = 0;
    l_begin_y = 0;
    r_begin_y = 0;
    l_end_y = 0;
    r_end_y = 0;
    switch (cross_state) {
    case NO_CROSS: {
        // 两边线中部为直线
        for (i = BUTTON - 20; i > BUTTON - 40; i -= 2) {
            if (leftline[i] > LEFT_LINE_BOUNDARY) {
                j++;
            }
            if (rightline[i] < RIGHT_LINE_BOUNDARY) {
                k++;
            }
        }
        // 两边线中后部都在边框附近
        for (i = BUTTON - 40; i > BUTTON - 70; i -= 2) {
            if (rightline[i] - leftline[i] > CROSS_DIFF) {
                l++;
            }
        }
        cross_out_j = j;
        cross_out_k = k;
        cross_out_l = l;
        cross_out_m = m;
        if (cross_out_j >= 7 && cross_out_k >= 7 && cross_out_l >= 5) {
            cross_state = SPOT_CROSS;
        }
        break;
    };
    case SPOT_CROSS: {
        // 两边线前部都在边框附近
        for (i = BUTTON; i > BUTTON - 40; i -= 2) {
            if (leftline[i] < LEFT_LINE_BOUNDARY) {
                j++;
            }
            if (rightline[i] > RIGHT_LINE_BOUNDARY) {
                k++;
            }
        }

        cross_out_j = j;
        cross_out_k = k;
        cross_out_l = l;
        cross_out_m = m;
        if (cross_out_j >= 13 && cross_out_k >= 13) {
            cross_state = IN_CROSS;
        }
        break;
    };
    case IN_CROSS: {
        // 两边线前部都不在边框附近
        for (i = BUTTON; i > BUTTON - 40; i -= 2) {
            if (leftline[i] > LEFT_LINE_BOUNDARY) {
                j++;
            }
            if (rightline[i] < RIGHT_LINE_BOUNDARY) {
                k++;
            }
        }

        cross_out_j = j;
        cross_out_k = k;
        cross_out_l = l;
        cross_out_m = m;
        if (cross_out_j >= 15 && cross_out_k >= 15) {
            cross_state = NO_CROSS;
        }
        break;
    };

    default: {
        self_log("cross_state error");
    }
    }
}

void cross_active(void) {
    int lb = 0, le = 0, rb = 0, re = 0, i = BUTTON;
    l_begin_y = r_begin_y = 50;
     l_end_y = r_end_y = 60;
    bool find_begin_flag = false;
    switch (cross_state) {
    case NO_CROSS: {
        break;
    };
    case SPOT_CROSS: {
        for (int i = BUTTON - 10; i > BUTTON - 100; i -= 2) {
            // 寻找结束补线的点:
            if (lb == 0 && leftline[i] - leftline[i - 2] > CROSS_DIFF) {
                if (leftline[i - 4] < LEFT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    lb= i;
                    while (leftline[lb] < LEFT_LINE_BOUNDARY) {
                        lb++;
                    }
                    l_end_y = lb;
                }
            }
            if (rb == 0 && rightline[i] - rightline[i - 2] < -CROSS_DIFF) {
                if (rightline[i - 4] > RIGHT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    rb = i;
                    while (rightline[rb] > RIGHT_LINE_BOUNDARY) {
                        rb++;
                    }
                    r_end_y = rb;
                }
            }
            // 寻找开始补线的点:
            if (le == 0 && leftline[i] - leftline[i - 2] < -CROSS_DIFF) {
                if (leftline[i - 4] > LEFT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    le = i;
                    while (leftline[le] < LEFT_LINE_BOUNDARY) {
                        le--;
                    }
                    l_begin_y = le;
                }
            }
            if (re == 0 && rightline[i] - rightline[i - 2] > CROSS_DIFF) {
                if (rightline[i - 4] < RIGHT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    re = i;
                    while (rightline[re] > RIGHT_LINE_BOUNDARY) {
                        re--;
                    }
                    r_begin_y = re;
                }
            }
        }
        fix_line_spot_cross(l_begin_y, l_end_y, leftline, true);
        fix_line_spot_cross(r_begin_y, r_end_y, rightline, false);
        // 重新计算中线
        switch_trackline();
        break;
    };
    case IN_CROSS: {
        for (int i = BUTTON - 20; i > BUTTON - 80; i -= 2) {
            // 寻找结束补线的点:
            // 不用找, 直接认为是左右下角的点

            // 寻找开始补线的点:
            if (le == 0 && leftline[i] - leftline[i - 2] < -CROSS_DIFF) {
                if (leftline[i - 4] > LEFT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    le = i;
                    while (leftline[le] < LEFT_LINE_BOUNDARY) {
                        le--;
                    }
                    l_end_y = le;
                }
            }

            if (re == 0 && rightline[i] - rightline[i - 2] > CROSS_DIFF) {
                if (rightline[i - 4] < RIGHT_LINE_BOUNDARY) {
                    // 找到一个赛道上的点
                    re = i;
                    while (rightline[re] > RIGHT_LINE_BOUNDARY) {
                        re--;
                    }
                    r_end_y = re;
                }
            }
        }
        fix_line_in_cross(l_end_y, leftline, true);
        fix_line_in_cross(r_end_y, rightline, false);
        // 重新计算中线
        switch_trackline();
        break;
    };
    default: {
        printf("cross_state error");
    }
    }
}


void cross_track(void){
    cross_check();
    cross_active();
}