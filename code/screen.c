#include "zf_common_headfile.h"

int tft180_y_max = 128;
int tft180_x_max = 160;
void show_line(void){

    for(uint16 i = 0; i < MT9V03X_H; i = i + 2){
        ips200_draw_point((uint16)trackline[i], i, RGB565_BLACK);//��ɫ����
    }
    for(uint16 i = 0; i < MT9V03X_H; i ++) {
        ips200_draw_point((uint16)leftline[i], i, RGB565_RED);//��ɫ����
        ips200_draw_point((uint16)rightline[i], i, RGB565_BLUE);//��ɫ����
        ips200_draw_point((uint16)centerline[i], i, RGB565_PURPLE);//��ɫ����
    }
}

void print_sidelines(void){
    int i = 0;
    for(i = 0; i < ipts0_num; i++){
        ips200_draw_point((uint16)(ipts0[i][0]), (uint16)(ipts0[i][1]), RGB565_RED);
    }
    tft180_show_int(COLUMN_LEFT_X, 5*CHAR_HEIGHT, ipts0[i][0], NUM_LENGTH);
    tft180_show_int(COLUMN_RIGHT_X, 5*CHAR_HEIGHT, ipts0[i][1], NUM_LENGTH);
    for(i = 0; i < ipts1_num; i++){
        ips200_draw_point((uint16)(ipts1[i][0]), (uint16)(ipts1[i][1]), RGB565_GREEN);
    }
}

void show_mark(void){
    for (int i = 0; i < 10; i++) {
        ips200_draw_point((uint16)(i), 20, RGB565_GREEN);
        ips200_draw_point((uint16)(i), 40, RGB565_GREEN);
        ips200_draw_point((uint16)(i), 60, RGB565_GREEN);
    }
}