#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;
boolean right_s = false;
int out_j = 0, out_k = 0;
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
    int i=0, k = 0;
    for (i = BUTTON; i >= 30; i -= 5) {
            // �ұ�������
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
 * @brief ʶ�𻷵�
 * @param sideline_begin ��ʼ���������
 * @param sideline_end �������������
 */
void round_check(
    void
){
    int i=0, j=0, k=0;

    switch (round_state) {
        case NO_ROUND : {
            for (i = BUTTON - 20; i >= BUTTON - 40 ; i -= 2) {
                // �������ǰ���ڱ߿򸽽�, �ж�Ϊ����
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
                // �����ǰ���ڱ߿򸽽�
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = BUTTON - 20; i > BUTTON - 80; i -= 2) {
                // �����в������ڻ��°벿
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
                // ������в���ǰ���ڱ߿򸽽�
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    k++;
                }
            }

            right_s = rightline_straight();
            out_k = k;

            // ����ƫ��
            if ( out_k > 12 && right_s && centerline[70] >= 70) {
                round_state = IN_ROUND;
            }
            break;
        }
        case IN_ROUND: {
            j = 0, k = 0;
            for ( i = BUTTON; i >= BUTTON - 60; i -= 3) {
                // ������в���ǰ���ڱ߿򸽽�
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // �ұ���ǰ��Ϊ�⻷
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
                // �ұ����в�б�ʴ�����(����ƫ/)
                 if(rightline[i]-rightline[i-3] >= -0.5) {
                    j++;
                 }
            }
            // ������ڱ߿򸽽�
            for ( i = BUTTON; i >= BUTTON - 30; i -= 3) {
                // ������в���ǰ���ڱ߿򸽽�
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
            // �����ǰ���ڱ߿򸽽�
            for ( i = BUTTON; i >= BUTTON - 40; i -= 2) {
                // ������в���ǰ���ڱ߿򸽽�
                if (leftline[i] > LEFT_LINE_BOUNDARY) {
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

            if ( out_j > 5 && out_k > 5) {
                round_state = OUT_ROUND;
            }
            break;
        };
        case OUT_ROUND: {
            j=0;
            // ����ߺ󲿻ָ�����
            for( i = BUTTON - 60; i > BUTTON - 80; i -= 2) {
                if ( 
                    ( (leftline[i+2] - leftline[i]) >= 5 ) &&
                    ( (leftline[i+2] - leftline[i]) >= 1)
                ) {
                    j++;//б�ʻָ�����
                }
            }
            // �ұ���ǰ���ָ�����
            for( i = BUTTON ; i > BUTTON - 60; i -= 3) {
                if (
                    ( ( rightline[i+3] - rightline[i] ) >= 5 ) &&
                    ( ( rightline[i+3] - rightline[i] ) >= 3 )
                ) {
                    k++;//б�ʻָ�����
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
 * @brief ����״̬�����ı�Ѳ��
 */
void round_active(
    void
){
    int i = 0;
    switch (round_state) {
        case NO_ROUND : {
            // ���øı�Ѳ��
            break;
        };
        case PRE_IN_ROUND : {
            // Ѳ����
            choose_tracktype(TRACK_RIGHT);
            break;
        }
        case READY_IN_ROUND : {
            // Ѳ����, ��PRE_IN_ROUND�б��Ĺ���
            // choose_tracktype(TRACK_RIGHT);
            break;
        };
        case IN_ROUND : {
            // ��Ѳ�ߵ��򻷵�����ƫ��
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
            // Ѳ����, ��PRE_IN_ROUND�б��Ĺ���
            // choose_tracktype(TRACK_RIGHT);
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