#include "zf_common_headfile.h"


int16 encoder_data_l = 1;
int16 encoder_data_r = 2;
/* int16 encoder_data_3 = 0;
int16 encoder_data_4 = 0; */

void read_encoder(void){
    encoder_data_l = encoder_get_count(ENCODER_LEFT);                              // 获取编码器计数
    encoder_clear_count(ENCODER_LEFT);                                             // 清空编码器计数

    encoder_data_r = encoder_get_count(ENCODER_RIGHT);                              // 获取编码器计数
    encoder_clear_count(ENCODER_RIGHT);                                             // 清空编码器计数
}