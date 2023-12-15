#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;
boolean right_s = false;
int out_j = 0, out_k = 0, out_rs = 0;
/**
 * todo:
 * ����ֻ�����󻷵�
*/

/**
 * @brief �ж��ұ����Ƿ�Ϊֱ��
 * @return true ֱ��
 * @return false ����ֱ��
 */
boolean rightline_straight(void) {
    int i = 0, k = 0;
    for (i = BUTTON - 5; i > BUTTON - 60; i -= 3) {
        if (rightline[i] - rightline[i + 5] < -1) {
            k++;
        } else if (
            // �ұ��߿�����, Ĭ��Ϊֱ��
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
 * @brief ʶ�𻷵�
 * @param sideline_begin ��ʼ���������
 * @param sideline_end �������������
 */
void round_check(
    void
){
    int i=0, j=0, k=0;
    out_j = 0, out_k = 0;
    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON; i >= BUTTON - 40 ; i -= 2) {
                // �����ǰ���ڱ߿򸽽�, �ж�Ϊ����
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
                // �����ǰ��Ϊ�ڻ�, ���ڱ߿򸽽�
                if (leftline[i] > LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // for (i = BUTTON - 40; i > BUTTON - 80; i -= 2) {
            //     // �����в������ڻ��°벿
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
                // ������ǰ���ڱ߿򸽽�
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
        //     // �����ڱ߿򸽽�
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
        //     //     // ������в��ڱ߿򸽽�
        //     //     if (leftline[i] < LEFT_LINE_BOUNDARY) {
        //     //         j++;
        //     //     }
        //     // }
        //     // for ( i = BUTTON - 60; i >= BUTTON - 80; i -= 2) {
        //     //     // ����ߺ�����
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
        //     // // ����ƫ��
        //     // if ( out_j > 8 && right_s && k > 7) {
        //     //     round_state = IN_ROUND;
        //     // }
        //     // break;
        //     // �����ڱ߿򸽽�
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
                // �ұ���ǰ��Ϊ�⻷
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
                // �ұ����в�б�ʴ�����(����ƫ/)
                 if (rightline[i]-rightline[i+3] >= 3) {
                    j++;
                 }
            }
            
            for ( i = BUTTON - 40; i >= BUTTON - 80; i -= 2) {
                // �ұ����в���ͻ��
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
            // �����ǰ���ڱ߿򸽽�
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // ������в���ǰ���ڱ߿򸽽�
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // �ұ���ǰ���ڱ߿򸽽�
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
            // // ������к��ڱ߿򸽽�
            // for( i = BUTTON; i > BUTTON - 60; i -= 2) {
            //     if ( leftline[i] < 25) {
            //         j++;
            //     }
            // }
            // �ұ���ǰ���ָ�����
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
            // �������ǰ���ָ�����
            for( i = BUTTON; i > BUTTON - 80; i -= 2) {
                if ( 
                    ( leftline[i] > LEFT_LINE_BOUNDARY ) &&
                    ( (leftline[i - 2] - leftline[i]) >= 1)
                ) {
                    j++; //б�ʻָ�����
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
 * @brief ����״̬�����ı�Ѳ��
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
            // Ѳ����
            choose_tracktype(TRACK_MID);
            break;
        };
        case BEFORE_ROUND : {
            // Ѳ����
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
            // Ѳ����, �� BEFORE_ROUND �б��Ĺ���
            choose_tracktype(TRACK_RIGHT);
            // ��Ѳ�ߵ��򻷵�����ƫ��
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
            // Ѳ����
            choose_tracktype(TRACK_MID);
            // ��Ѳ�ߵ��򻷵�����ƫ��
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
            // Ѳ����
            choose_tracktype(TRACK_RIGHT);
            break;
        };
        case READY_OUT_ROUND : {
            // Ѳ����
            choose_tracktype(TRACK_MID);
            break;
        };
        case OUT_ROUND : {
            // ��Ѳ�ߵ������������ƫ��
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
            // Ѳ����
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
