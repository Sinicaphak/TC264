#include "zf_common_headfile.h"

int tft180_y_max = 128;
int tft180_x_max = 160;
void show_line(void){

    for(uint16 i = 0; i < MT9V03X_H; i = i + 2){
        ips200_draw_point((uint16)trackline[i], i, RGB565_BLACK);//黑色跟踪
    }
    for(uint16 i = 0; i < MT9V03X_H; i ++) {
        ips200_draw_point((uint16)leftline[i], i, RGB565_RED);//红色左线
        ips200_draw_point((uint16)rightline[i], i, RGB565_BLUE);//蓝色右线
        ips200_draw_point((uint16)centerline[i], i, RGB565_PURPLE);//紫色中线
    }
}
