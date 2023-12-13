#include "zf_common_headfile.h"

int tft180_y_max = 128;
int tft180_x_max = 160;
void show_line(void){

    for(uint16 i = 0; i < MT9V03X_H; i ++) {
        ips200_draw_point((uint16)leftline[i], i, RGB565_RED);//红色左线
        ips200_draw_point((uint16)rightline[i], i, RGB565_BLUE);//蓝色右线
        ips200_draw_point((uint16)centerline[i], i, RGB565_PURPLE);//紫色中线
    }
    for(uint16 i = 0; i < MT9V03X_H; i = i + 2){
        ips200_draw_point((uint16)trackline[i], i, RGB565_BLACK);//黑色跟踪
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
    int i, j, half_h, half_w;
    half_h = MT9V03X_H / 2;
    half_w = MT9V03X_W / 2;
    for (i = -5; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (j % 2 == 0) {
                ips200_draw_point((uint16)(i + half_w), (j * 20), RGB565_BLACK);
            } else {
                ips200_draw_point((uint16)(i + half_w), (j * 20), RGB565_CYAN);
            } 
        }
    }

    for (i = -5; i < 6; i++) {
        for (j = 0; j < 10; j++) {
            if (j % 2 == 0) {
                ips200_draw_point((j * 20), (i + half_h), RGB565_CYAN);
            } else {
                ips200_draw_point((j * 20), (i + half_h), RGB565_BLACK);
            } 
        }
    }
}