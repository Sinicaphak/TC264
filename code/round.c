#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;
boolean right_s = false;
int out_j = 0, out_k = 0, out_rs = 0;
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
    int i = 0, k = 0;
    for (i = BUTTON - 5; i > BUTTON - 60; i -= 3) {
        if (rightline[i] - rightline[i + 5] < -1) {
            k++;
        } else if (
            // 右边线看不见, 默认为直线
            rightline[i] > RIGHT_LINE_BOUNDARY &&
            rightline[i - 1] > RIGHT_LINE_BOUNDARY &&
            rightline[i - 2] > RIGHT_LINE_BOUNDARY
        ) {
            k++;
        } else if (
            rightline[i] - rightline[i + 5] >= 2
        ) {
            k = 0;
        }
        out_rs = k;
    }
    return (k >= 15) ? true : false;
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
    out_j = 0, out_k = 0;
    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON; i >= BUTTON - 40 ; i -= 2) {
                // 左边线前部在边框附近, 判断为丢线
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            out_j = j;

            if (out_j >= 15 && rightline_straight()) {
                round_state = BEFORE_ROUND;
            }
            break;
        };
        case BEFORE_ROUND : {
            for (i = BUTTON; i > BUTTON - 40; i -= 2) {
                // 左边线前部为内环, 不在边框附近
                if (leftline[i] > LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // for (i = BUTTON - 40; i > BUTTON - 80; i -= 2) {
            //     // 左线中部出现内环下半部
            //     if (leftline[i] - leftline[i + 2] > 2) {
            //         k++;
            //     }
            // }

            right_s = rightline_straight();
            out_j = j;
            // out_k = k;

            if (out_j >= 12 && right_s) {
                round_state = MID_ROUND;
            }
            break;
        };
        case MID_ROUND : {
           for (i = BUTTON - 20; i > BUTTON - 70; i -= 3) {
                // 左线中前部在边框附近
                // if (leftline[i] - leftline[i + 3] >= 1) {
                //     j++;
                // } else if (leftline[i] - leftline[i + 3] <= -1) {
                //     j++;
                // }
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            out_j = j;
            right_s = rightline_straight();

            if (out_j > 12 && right_s) {
                round_state = IN_ROUND;
            }
            break;
        }
        // case MID_ROUND : {
        //     // 左线在边框附近
        //     for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
        //         if (leftline[i] < LEFT_LINE_BOUNDARY) {
        //             j++;
        //         }
        //     }
        //     right_s = rightline_straight();
        //     out_j = j;
        //     if ( out_j > 8 && right_s) {
        //         round_state = READY_IN_ROUND;
        //     }
        //     break;
        // };
        // case READY_IN_ROUND: {
        //     // for ( i = BUTTON - 40; i >= BUTTON - 60; i -= 2) {
        //     //     // 左边线中部在边框附近
        //     //     if (leftline[i] < LEFT_LINE_BOUNDARY) {
        //     //         j++;
        //     //     }
        //     // }
        //     // for ( i = BUTTON - 60; i >= BUTTON - 80; i -= 2) {
        //     //     // 左边线后部正常
        //     //     if (
        //     //         (leftline[i] - leftline[i - 2] < 0) &&
        //     //         (leftline[i] > LEFT_LINE_BOUNDARY )
        //     //     ){
        //     //         k++;
        //     //     } else {
        //     //         k--;
        //     //     }
        //     // }
        //     // right_s = rightline_straight();
        //     // out_j = j;
        //     // out_k = k;
        //     // // 中线偏左
        //     // if ( out_j > 8 && right_s && k > 7) {
        //     //     round_state = IN_ROUND;
        //     // }
        //     // break;
        //     // 左线在边框附近
        //     for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
        //         if (leftline[i] < LEFT_LINE_BOUNDARY) {
        //             j++;
        //         } else {
        //             j--;
        //         }
        //     }
        //     right_s = rightline_straight();
        //     out_j = j;
        //     if ( out_j > 13 && right_s) {
        //         round_state = IN_ROUND;
        //     }
        //     break;
        // }
        case IN_ROUND: {
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // 右边线前部为外环
                if (rightline[i] - rightline[i + 2] <= -3) {
                    k++;
                }
            }

            out_k = k;

            if (out_k > 8) {
                round_state = ROUNDING;
            }
            break;
        }
        case ROUNDING: {
             j = 0, k = 0;
             for ( i = BUTTON - 40; i > BUTTON - 80; i -= 2) {
                // 右边线中部斜率大于零(向右偏/)
                 if (rightline[i]-rightline[i+3] >= 3) {
                    j++;
                 }
            }
            
            for ( i = BUTTON - 40; i >= BUTTON - 80; i -= 2) {
                // 右边线中部分突变
                if (rightline[i] - rightline[i - 2] >= 4 ) {
                    if (rightline[i + 2] - rightline[i] < 1) {
                        if (rightline[i - 2] - rightline[i - 4] < 1) {
                            k++;
                        }
                    }
                }
            }

            out_j = j;
            out_k = k;

            if ( out_j > 7 || k > 0){
                round_state = READY_OUT_ROUND;
            }
            break;
        };
        case READY_OUT_ROUND: {
            // 左边线前部在边框附近
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // 左边线中部和前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
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

            if ( out_j >= 12 && out_k >= 12) {
                round_state = OUT_ROUND;
            }
            break;
        };
        case OUT_ROUND: {
            // // 左边线中后部在边框附近
            // for( i = BUTTON; i > BUTTON - 60; i -= 2) {
            //     if ( leftline[i] < 25) {
            //         j++;
            //     }
            // }
            // 右边线前部恢复正常
            for( i = BUTTON ; i > BUTTON - 60; i -= 3) {
                if (
                    ( ( rightline[i + 3] - rightline[i] ) >= 2 )
                ) {
                    k++;
                }
            }

            out_k = k;
            right_s = rightline_straight();

            if( out_k >= 15 && right_s) {
                round_state = ROUND_END;
            }
            break;
        };
        case ROUND_END: {
            // 左边线中前部恢复正常
            for( i = BUTTON; i > BUTTON - 80; i -= 2) {
                if ( 
                    ( leftline[i] > LEFT_LINE_BOUNDARY ) &&
                    ( (leftline[i - 2] - leftline[i]) >= 1)
                ) {
                    j++; //斜率恢复正常
                }
            }

            right_s = rightline_straight();
            out_j = j;

            if ( out_j > 27 && right_s) {
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
    if (round_state != NO_ROUND) {
        target_speed = ROUND_SPEED;
    } else {
        target_speed = DEF_SPEED;
    }
    switch (round_state) {
        case NO_ROUND : {
            // 巡中线
            choose_tracktype(TRACK_MID);
            break;
        };
        case BEFORE_ROUND : {
            // 巡右线
            choose_tracktype(TRACK_RIGHT);
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = (int)limit_amplitude_upper_lower(
                    (double)(trackline[i] + BEFORE_ROUND_SHIFT),
                    2,
                    MT9V03X_W - 2
                );
            }
            break;
        }
        case MID_ROUND : {
            // 巡右线, 在 BEFORE_ROUND 中被改过了
            choose_tracktype(TRACK_RIGHT);
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 30; i++) {
                trackline[i] = (int)limit_amplitude_upper_lower(
                    (double)(trackline[i] + MID_ROUND_SHIFT),
                    2,
                    MT9V03X_W - 2
                );
            }
            break;
        }
        case IN_ROUND : {
            // 巡中线
            choose_tracktype(TRACK_MID);
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = (int)limit_amplitude_upper_lower(
                    (double)(trackline[i + 1] + IN_ROUND_SHIFT),
                    2,
                    MT9V03X_W - 2
                );
            }
            break;
        };
        case ROUNDING : {
            // 巡右线
            choose_tracktype(TRACK_RIGHT);
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
                trackline[i] = trackline[i + 1] + OUT_ROUND_SHIFT;
                if (trackline[i] > MT9V03X_W - 2) {
                    trackline[i] = MT9V03X_W - 2;
                } else if (trackline[i] < 2) {
                    trackline[i] = 2;
                }
            }
            break;
        };
        case ROUND_END : {
            // 巡右线
            choose_tracktype(TRACK_RIGHT);
            break;
        };
    }
}

void round_track(    
    void
){
    round_check();
    round_active();
}
