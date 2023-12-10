#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;

/**
 * todo:
 * 现在只能跑左环岛
*/

/**
 * @brief 识别环岛
 * @param sideline_begin 开始处理的行数
 * @param sideline_end 结束处理的行数
 */
void round_check(
    void
){
    int i=0, j=0, k=0, z=0;

    switch (round_state) {
        case NO_ROUND : {
            // 判断有无入环点
            // 左边丢线右边没有, 则为有入环点
            for (i = 0; i <= 20; i++) {
                // 左边线在边框附近, 判断为丢线
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = 22; i <= 52; i += 5) {
                // 左边线与相邻线x坐标相差大于阈值, 判断为断线
                if (leftline[i] - leftline[i + 5] > ROUND_BREAK_THS) {
                    z++;
                }
            }
            for (i = 0; i <= 30; i += 5) {
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
            if (j > 4 && z > 3 && k > 5) {
                round_state = READY_IN_ROUND;
            }
            break;
        };
        case READY_IN_ROUND : {
            // 判断入环点是否消失, 有无内环点
            j = 0, k = 0, z = 0;
            for (i = 2; i < 25; i+=2) {
                // 左边线在边框附近, 判断为丢线
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // for (i = 33; i < 60; i += 3) {
            //     // 左线中部在内环下半部
            //     if (leftline[i] - leftline[i + 3] < -0.8) {
            //         k++;
            //     }
            // }
            for(i=0;i<=16;i+=2) {
                // 右边线正常
                if (rightline[i] - rightline[i + 5] < -1.8) { 
                    z++;
                }
                else if(
                    rightline[i] > RIGHT_LINE_BOUNDARY &&
                    rightline[i+1] > RIGHT_LINE_BOUNDARY &&
                    rightline[i+2] > RIGHT_LINE_BOUNDARY &&
                    rightline[i+3] > RIGHT_LINE_BOUNDARY &&
                    rightline[i+4] > RIGHT_LINE_BOUNDARY
                ) {
                    z=0;
                    break;
                }
            }
            if (j >4&& k >=5 && z >3) {
                round_state = IN_ROUND;
            }
            break;
        };
        case IN_ROUND: {
            k=0,j=0;
            for(i=10;i<=28;i+=2) {
                if (leftline[i] < 5) {
                    k++;
                }
            }
            for (i=58;i>51;i--) {
                if(rightline[i] < 173) {
                    j++;
                }
            }
            if(k>=5&&j>4&&centerline[15]<=65) {
                round_state=ROUNDING;
            }

            break;
        }
        case ROUNDING: {
             j=0;z=0;
             for (i=13;i<40;i+=2) {
                 if(rightline[i]-rightline[i-3]>=2) {
                    j=1;
                    continue;
                 } else if(j) {
                    if(rightline[i+3]-rightline[i]<=0) {
                        j=0;break;
                    }
                 }
            }

             for (i=10;i<=28;i+=2) {
                if(leftline[i]<5) {
                    z++;
                }
            }

             if (j&&rightline[3]>=180&&z>=5){
                round_state=READY_OUT_ROUND;
             }
            break;
        };
        case READY_OUT_ROUND: {
            j=0,k=0;
           for(i=20;i<60;i+=2) {
               if(leftline[i]<5) {
                    j++;
                }
           }
           for(i=20;i<60;i+=2) {
                if(rightline[i]>183) { 
                    k++;
                }
             }
           if(j>10&&k>12) {
                round_state=NO_ROUND;
            }
            break;
        };
        case OUT_ROUND: {
            j=0;
            for(i=20;i<50;i+=2) {
                if(rightline[i+3]-rightline[i]<=5&&rightline[i+3]-rightline[i]>=3) {
                    j++;//斜率恢复正常
                }
            }
            for(i=10;i<50;i+=2) {
                if(leftline[i]<5) {
                    k++;
                }
            }
            if(j>=10&&k>8) {
                round_state=NO_ROUND;
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
        case READY_IN_ROUND : {
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 1; i++) {
                trackline[i] = trackline[i] + READY_IN_ROUND_SHIFT;
            }
            break;
        };
        case IN_ROUND : {
            // 将巡线点向环岛方向偏移
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = trackline[i + 1] + IN_ROUND_SHIFT;
            }
            break;
        };
        case ROUNDING : {
            // 巡右线
            track_type = TRACK_RIGHT;
            switch_trackline();
            break;
        };
        case READY_OUT_ROUND : {
            // 巡中线
            track_type = TRACK_MID;
            switch_trackline();
            break;
        };
        case OUT_ROUND : {
            // 将巡线点向出环岛方向偏移
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = trackline[i + 1] - IN_ROUND_SHIFT;
            }
            break;
            break;
        };
    }
}

void roun_track(    
    void
){
    round_check();
//    round_active();
}