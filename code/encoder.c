#include "zf_common_headfile.h"


int16 encoder_data_l = 1;
int16 encoder_data_r = 2;
/* int16 encoder_data_3 = 0;
int16 encoder_data_4 = 0; */

void read_encoder(void){
    encoder_data_l = encoder_get_count(ENCODER_LEFT);                              // ��ȡ����������
    encoder_clear_count(ENCODER_LEFT);                                             // ��ձ���������

    encoder_data_r = encoder_get_count(ENCODER_RIGHT);                              // ��ȡ����������
    encoder_clear_count(ENCODER_RIGHT);                                             // ��ձ���������
}