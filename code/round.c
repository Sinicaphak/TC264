#include "zf_common_headfile.h"

enum ROUND_STATE round_state = NO_ROUND;

/**
 * todo:
 * ����ֻ�����󻷵�
*/

/**
 * @brief ʶ�𻷵�
 * @param sideline_begin ��ʼ���������
 * @param sideline_end �������������
 */
void round_check(
    void
){
    int i=0, j=0, k=0, z=0;

    switch (round_state) {
        case NO_ROUND : {
            // �ж������뻷��
            // ��߶����ұ�û��, ��Ϊ���뻷��
            for (i = 0; i <= 20; i++) {
                // ������ڱ߿򸽽�, �ж�Ϊ����
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            for (i = 22; i <= 52; i += 5) {
                // �������������x������������ֵ, �ж�Ϊ����
                if (leftline[i] - leftline[i + 5] > ROUND_BREAK_THS) {
                    z++;
                }
            }
            for (i = 0; i <= 30; i += 5) {
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
            if (j > 4 && z > 3 && k > 5) {
                round_state = READY_IN_ROUND;
            }
            break;
        };
        case READY_IN_ROUND : {
            // �ж��뻷���Ƿ���ʧ, �����ڻ���
            j = 0, k = 0, z = 0;
            for (i = 2; i < 25; i+=2) {
                // ������ڱ߿򸽽�, �ж�Ϊ����
                if (leftline[i] < LEFT_LINE_BOUNDARY) {
                    j++;
                }
            }
            // for (i = 33; i < 60; i += 3) {
            //     // �����в����ڻ��°벿
            //     if (leftline[i] - leftline[i + 3] < -0.8) {
            //         k++;
            //     }
            // }
            for(i=0;i<=16;i+=2) {
                // �ұ�������
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
                    j++;//б�ʻָ�����
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
        case READY_IN_ROUND : {
            // ��Ѳ�ߵ��򻷵�����ƫ��
            for (i = 0; i < MT9V03X_H - 1; i++) {
                trackline[i] = trackline[i] + READY_IN_ROUND_SHIFT;
            }
            break;
        };
        case IN_ROUND : {
            // ��Ѳ�ߵ��򻷵�����ƫ��
            for (i = 0; i < MT9V03X_H - 2; i++) {
                trackline[i] = trackline[i + 1] + IN_ROUND_SHIFT;
            }
            break;
        };
        case ROUNDING : {
            // Ѳ����
            track_type = TRACK_RIGHT;
            switch_trackline();
            break;
        };
        case READY_OUT_ROUND : {
            // Ѳ����
            track_type = TRACK_MID;
            switch_trackline();
            break;
        };
        case OUT_ROUND : {
            // ��Ѳ�ߵ������������ƫ��
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