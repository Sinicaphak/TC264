#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;
enum ROUND_DIR round_dir = NO_DIR;
boolean right_s = false;
int out_j = 0, out_k = 0, out_rs = 0;
int out_hrl = 0, out_hrr = 0;
/**
 * todo:
 * 现在只能跑左环岛
*/

/**
 * @brief 判断右边线是否为直线
 * @param tolerate_invisible true时把边缘附近的点也算作直线
 * @return true 直线
 * @return false 不是直线
 */
boolean rightline_straight(boolean tolerate_invisible) {
    int i = 0, k = 0, j = 0;
    for (i = BUTTON - 6; i > BUTTON - 90; i -= 3) {
        if (rightline[i] - rightline[i + 3] < -1) {
            k++;
        }
        // 右边线看不见要怎么处理 
        else if (
            rightline[i] > RIGHT_LINE_BOUNDARY &&
            rightline[i - 1] > RIGHT_LINE_BOUNDARY &&
            rightline[i - 2] > RIGHT_LINE_BOUNDARY
        ) {
            if ( tolerate_invisible ) {
                // 默认为直线
                k++;
            } else {
                j++;
                if (j >= 2) {
                    k = 0;
                }
            } 
        } else if (
            rightline[i] - rightline[i + 5] >= 2
        ) {
            k = 0;
        }
        out_rs = k;
    }
    return (k >= 16) ? true : false;
}
/**
 * @brief 判断左边线是否为直线
 * @param tolerate_invisible true时把边缘附近的点也算作直线
 * @return true 直线
 * @return false 不是直线
 */
boolean leftline_straight(boolean tolerate_invisible) {
    int i = 0, k = 0, j = 0;
    for (i = BUTTON - 6; i > BUTTON - 90; i -= 3) {
        if (leftline[i] - leftline[i + 3] > 1) {
            k++;
        }
        // 左边线看不见要怎么处理 
        else if (
            leftline[i] < LEFT_LINE_BOUNDARY &&
            leftline[i - 1] < LEFT_LINE_BOUNDARY &&
            leftline[i - 2] < LEFT_LINE_BOUNDARY
        ) {
            if ( tolerate_invisible ) {
                // 默认为直线
                k++;
            } else {
                j++;
                if (j >= 2) {
                    k = 0;
                }
            } 
        } else if (
            leftline[i] - leftline[i + 5] <= 2
        ) {
            k = 0;
        }
        out_rs = k;
    }
    return (k >= 16) ? true : false;
}

/**
 * @brief 简单判断环岛元素在哪边
 */
void has_round(void) {
    int i = 0, l = 0, r = 0;
    out_hrl = 0, out_hrr = 0;
    if (round_state != NO_ROUND) {
        return;
    }
    for (i = BUTTON - 20; i > BUTTON - 80; i -= 5) {
        if (leftline[i] < LEFT_LINE_BOUNDARY) {
            l++;
        }
        if (rightline[i] > RIGHT_LINE_BOUNDARY) {
            r++;
        }
    }
    out_hrl = l;
    out_hrr = r;
    if (l >= 2 && r >= 2) {
        round_dir = NO_DIR;
    } else if (l >= 2 && r < 2) {
        round_dir = LEFT_DIR;
    } else if (r >= 2 && l < 2) {
        round_dir = RIGHT_DIR;
    } else {
        round_dir = NO_DIR;
    }
}
/**
 * @brief 识别左环岛
 */
void left_round_check(
    void
){
    int i=0, j=0, k=0;
    out_j = 0, out_k = 0;
    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON - 40; i >= BUTTON - 80 ; i -= 2) {
                // 左边线前部在边框附近, 判断为丢线
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = BUTTON - 60; i >= BUTTON - 100; i -= 2) {
                // 左线前部出现内环中部, 斜率先变大后变小 
                if (
                    (leftline[i] - leftline[i + 4] >= 2) &&
                    (leftline[i] - leftline[i - 4] >= 2)    
                ) {
                    k++;
                }
            }
            out_j = j;
            out_k = k;
            right_s = rightline_straight(false);
            if (out_j >= 12 && right_s && out_k >= 1) {
                round_state = BEFORE_ROUND;
            }
            // if (out_j >= 17 && right_s) {
            //     round_state = BEFORE_ROUND;
            // }
            break;
        };
        case BEFORE_ROUND : {
            for (i = BUTTON; i > BUTTON - 40; i -= 2) {
                // 左边线前部为内环, 不在边框附近
                if (leftline[i] > LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            right_s = rightline_straight(true);
            out_j = j;

            if (out_j >= 12 && right_s) {
                round_state = MID_ROUND;
            }
            break;
        };
        case MID_ROUND : {
           for (i = BUTTON - 20; i > BUTTON - 70; i -= 3) {
                // 左线中前部在边框附近
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            out_j = j;
            right_s = rightline_straight(true);

            if (out_j > 12 && right_s) {
                round_state = IN_ROUND;
            }
            break;
        }
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
                if (rightline[i] - rightline[i - 2] <= -4 ) {
                    if (rightline[i + 2] - rightline[i] <= 2) {
                        if (rightline[i - 2] - rightline[i - 4] <= 2) {
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
            // 右边线前部恢复正常
            for( i = BUTTON ; i > BUTTON - 60; i -= 3) {
                if (
                    ( ( rightline[i + 3] - rightline[i] ) >= 2 )
                ) {
                    k++;
                }
            }

            out_k = k;
            right_s = rightline_straight(true);

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

            right_s = rightline_straight(true);
            out_j = j;

            if ( out_j > 27 && right_s) {
                round_state = NO_ROUND;
            }
            round_dir = NO_DIR;
            break;
        };
        
    }
}
/**
 * @brief 识别右环岛
 */
void right_round_check(
    void
){
    int i=0, j=0, k=0;
    out_j = 0, out_k = 0;
    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON; i >= BUTTON - 40 ; i -= 2) {
                // 右边线前部在边框附近, 判断为丢线
                if (rightline[i] > RIGHT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = BUTTON - 60; i >= BUTTON - 100; i -= 2) {
                // 右线前部出现内环中部, 斜率先变大后变小 
                if (
                    (rightline[i] - rightline[i + 4] <= -2) &&
                    (rightline[i] - rightline[i - 4] <= -2)    
                ) {
                    k++;
                }
            }
            out_j = j;
            out_k = k;

            if (out_j >= 17 && leftline_straight(false) && out_k >= 1) {
                round_state = BEFORE_ROUND;
            }
            break;
        };
        case BEFORE_ROUND : {
            for (i = BUTTON; i > BUTTON - 40; i -= 2) {
                // 右边线前部为内环, 不在边框附近
                if (rightline[i] < RIGHT_LINE_BOUNDARY) {
                    j++;
                }
            }
            right_s = leftline_straight(true);
            out_j = j;

            if (out_j >= 12 && right_s) {
                round_state = MID_ROUND;
            }
            break;
        };
        case MID_ROUND : {
           for (i = BUTTON - 20; i > BUTTON - 70; i -= 3) {
                // 左线中前部在边框附近
                if (rightline[i] > RIGHT_LINE_BOUNDARY) {
                    j++;
                }
            }
            out_j = j;
            right_s = leftline_straight(true);

            if (out_j > 12 && right_s) {
                round_state = IN_ROUND;
            }
            break;
        }
        case IN_ROUND: {
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // 左边线前部为外环
                if (leftline[i] - leftline[i + 2] >= 3) {
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
                // 左边线中部斜率小于零(向左偏\)
                 if (leftline[i]-leftline[i+3] <= -3) {
                    j++;
                 }
            }
            
            for ( i = BUTTON - 40; i >= BUTTON - 80; i -= 2) {
                // 左边线中部分突变
                if (leftline[i] - leftline[i - 2] >= 4 ) {
                    if (leftline[i + 2] - leftline[i] >= -1) {
                        if (leftline[i - 2] - leftline[i - 4] >= -1) {
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
            // 左边线前部恢复正常
            for( i = BUTTON ; i > BUTTON - 60; i -= 3) {
                if (
                    ( ( leftline[i - 3] - leftline[i] ) >= 2 )
                ) {
                    k++;
                }
            }

            out_k = k;
            right_s = leftline_straight(true);

            if( out_k >= 15 && right_s) {
                round_state = ROUND_END;
            }
            break;
        };
        case ROUND_END: {
            // 右边线中前部恢复正常
            for( i = BUTTON; i > BUTTON - 80; i -= 2) {
                if ( 
                    ( rightline[i] < RIGHT_LINE_BOUNDARY ) &&
                    ( (rightline[i] - rightline[i - 2]) >= 1)
                ) {
                    j++; //斜率恢复正常
                }
            }

            right_s = leftline_straight(true);
            out_j = j;

            if ( out_j > 27 && right_s) {
                round_state = NO_ROUND;
            }
            round_dir = NO_DIR;
            break;
        };
        
    }
}

/**
 * @brief 根据状态环岛改变巡线
 */
void left_round_active(
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
                    (double)(trackline[i] + L_BEFORE_ROUND_SHIFT),
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
                    (double)(trackline[i] + L_MID_ROUND_SHIFT),
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
                    (double)(trackline[i + 1] + L_IN_ROUND_SHIFT),
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
                trackline[i] = trackline[i + 1] + L_OUT_ROUND_SHIFT;
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

void right_round_active(
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
            // 巡左线
            choose_tracktype(TRACK_LEFT);
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = (int)limit_amplitude_upper_lower(
                    (double)(trackline[i] + R_BEFORE_ROUND_SHIFT),
                    2,
                    MT9V03X_W - 2
                );
            }
            break;
        }
        case MID_ROUND : {
            // 巡左线, 在 BEFORE_ROUND 中被改过了
            choose_tracktype(TRACK_LEFT);
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 30; i++) {
                trackline[i] = (int)limit_amplitude_upper_lower(
                    (double)(trackline[i] + R_MID_ROUND_SHIFT),
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
                    (double)(trackline[i + 1] + R_IN_ROUND_SHIFT),
                    2,
                    MT9V03X_W - 2
                );
            }
            break;
        };
        case ROUNDING : {
            // 巡右线
            choose_tracktype(TRACK_LEFT);
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
                trackline[i] = trackline[i + 1] + R_OUT_ROUND_SHIFT;
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
            choose_tracktype(TRACK_LEFT);
            break;
        };
    }
}

void round_track(    
    void
){  
    has_round();
    switch (round_dir) {
        case LEFT_DIR : {
            left_round_check();
            left_round_active();
            break;
        };
        case RIGHT_DIR : {
            right_round_check();
            right_round_active();
            break;
        };
        case NO_DIR : {
            break;
        };
        default : {
            zf_log(0, "round_dir error");
            break;
        }
    }
    // left_round_check();
    // left_round_active();
}
