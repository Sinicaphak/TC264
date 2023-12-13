#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;
boolean right_s = false;
int out_j = 0, out_k = 0;
/**
 * todo:
 * 现在只能跑左环岛
*/

/**
 * @brief 判断右边线是否为直线
 * @return true 直线
 * @return false 不是直线
 */
boolean rightline_straight(void) {
    int i=0, k = 0;
    for (i = BUTTON; i >= 30; i -= 5) {
            // 右边线正常
            if (rightline[i] - rightline[i + 5] < -1.8) {
                k++;
            } else if (
                rightline[i] > RIGHT_LINE_BOUNDARY &&
                rightline[i + 1] > RIGHT_LINE_BOUNDARY &&
                rightline[i + 2] > RIGHT_LINE_BOUNDARY &&
                rightline[i + 3] > RIGHT_LINE_BOUNDARY &&
                rightline[i + 4] > RIGHT_LINE_BOUNDARY
            ) {
                k = 0;
                break;
            }
        }
    return (k > 5) ? true : false;
}

/**
 * @brief 识别环岛
 * @param sideline_begin 开始处理的行数
 * @param sideline_end 结束处理的行数
 */
void round_check(
    void
){
    int i=0, j=0, k=0;

    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON - 20; i >= BUTTON - 40 ; i -= 2) {
                // 左边线中前部在边框附近, 判断为丢线
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // right_s = rightline_straight();
            // out_j = j;
            // if (out_j >= 3 && right_s) {
            //     round_state = PRE_IN_ROUND;
            // }
            if (j >= 3 && rightline_straight()) {
                round_state = PRE_IN_ROUND;
            }
            break;
        };
        case PRE_IN_ROUND : {
            j = 0, k = 0;
            for (i = BUTTON; i > BUTTON - 40; i -= 2) {
                // 左边线前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = BUTTON - 20; i > BUTTON - 80; i -= 2) {
                // 左线中部出现内环下半部
                if (leftline[i] - leftline[i + 2] > 2) {
                    k++;
                }
            }

            right_s = rightline_straight();
            out_j = j;
            out_k = k;

            if (out_j > 10 && out_k > 10 && right_s) {
                round_state = READY_IN_ROUND;
            }
            // if (out_j > 4 && right_s ) {
            //     round_state = READY_IN_ROUND;
            // }
            break;
        };
        case READY_IN_ROUND: {
            k = 0;
            for ( i = BUTTON; i >= BUTTON - 60; i -= 3) {
                // 左边线中部和前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    k++;
                }
            }

            right_s = rightline_straight();
            out_k = k;

            // 中线偏左
            if ( out_k > 12 && right_s && centerline[70] >= 70) {
                round_state = IN_ROUND;
            }
            break;
        }
        case IN_ROUND: {
            j = 0, k = 0;
            for ( i = BUTTON; i >= BUTTON - 60; i -= 3) {
                // 左边线中部和前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // 右边线前部为外环
                if (rightline[i] - rightline[i + 2] > 1.2) {
                    k++;
                }
            }

            out_j = j;
            out_k = k;

            if (out_j > 12 && out_k >= 10) {
                round_state = ROUNDING;
            }
            break;
        }
        case ROUNDING: {
             j = 0, k = 0;
             for ( i = BUTTON - 40; i > BUTTON - 80; i -= 2) {
                // 右边线中部斜率大于零(向右偏/)
                 if(rightline[i]-rightline[i-3] >= -0.5) {
                    j++;
                 }
            }
            // 左边线在边框附近
            for ( i = BUTTON; i >= BUTTON - 30; i -= 3) {
                // 左边线中部和前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    k++;
                }
            }

            out_j = j;
            out_k = k;

             if ( out_j >= 3 && out_k >= 5 ){
                round_state=READY_OUT_ROUND;
            }
            break;
        };
        case READY_OUT_ROUND: {
            j = 0, k = 0;
            // 左边线前部在边框附近
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // 左边线中部和前部在边框附近
                if (leftline[i] > LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // 右边线前部在边框附近
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                if (rightline[i] > RIGHT_LINE_BOUNDARY) {
                    k++;
                }
            }

            out_j = j;
            out_k = k;

            if ( out_j > 5 && out_k > 5) {
                round_state = OUT_ROUND;
            }
            break;
        };
        case OUT_ROUND: {
            j=0;
            // 左边线后部恢复正常
            for( i = BUTTON - 60; i > BUTTON - 80; i -= 2) {
                if ( 
                    ( (leftline[i+2] - leftline[i]) >= 5 ) &&
                    ( (leftline[i+2] - leftline[i]) >= 1)
                ) {
                    j++;//斜率恢复正常
                }
            }
            // 右边线前部恢复正常
            for( i = BUTTON ; i > BUTTON - 60; i -= 3) {
                if (
                    ( ( rightline[i+3] - rightline[i] ) >= 5 ) &&
                    ( ( rightline[i+3] - rightline[i] ) >= 3 )
                ) {
                    k++;//斜率恢复正常
                }
            }

            out_j = j;
            out_k = k;

            if( out_j >= 7 && out_k >= 7) {
                round_state = NO_ROUND;
            }
            break;
        };

    }
}

/**
 * @brief 根据状态环岛改变巡线
 */
void round_active(
    void
){
    int i = 0;
    switch (round_state) {
        case NO_ROUND : {
            // 不用改变巡线
            break;
        };
        case PRE_IN_ROUND : {
            // 巡右线
            choose_tracktype(TRACK_RIGHT);
            break;
        }
        case READY_IN_ROUND : {
            // 巡右线, 在PRE_IN_ROUND中被改过了
            // choose_tracktype(TRACK_RIGHT);
            break;
        };
        case IN_ROUND : {
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = trackline[i + 1] + IN_ROUND_SHIFT;
                if (trackline[i] > MT9V03X_W - 2) {
                    trackline[i] = MT9V03X_W - 2;
                } else if (trackline[i] < 2) {
                    trackline[i] = 2;
                }
            }
            break;
        };
        case ROUNDING : {
            // 巡右线, 在PRE_IN_ROUND中被改过了
            // choose_tracktype(TRACK_RIGHT);
            break;
        };
        case READY_OUT_ROUND : {
            // 巡中线
            choose_tracktype(TRACK_MID);
            break;
        };
        case OUT_ROUND : {
            // 将巡线点向出环岛方向偏移
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = trackline[i + 1] - IN_ROUND_SHIFT;
            }
            break;
        };
    }
}

void round_track(    
    void
){
    round_check();
    // round_active();
}