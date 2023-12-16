#include "zf_common_headfile.h"

int16 trackline[MT9V03X_H];//跟踪线
// enum track_type_e track_type = TRACK_MID;//默认循中线
//将边线赋值给循迹跟踪线
void switch_trackline(void){
    int temp;
    if(track_type == TRACK_MID){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = centerline[i];//循中线
        }
    }
    if(track_type == TRACK_LEFT){
        // for(int i = 0; i < MT9V03X_H;i ++){
        //     trackline[i] = (leftline[i] + (0.2 * PIX_PER_METER)) > 187 ? 187 : (int16)(leftline[i] + 0.2 * PIX_PER_METER);//循左线，左线应向右侧偏移道路宽度一半，即0.2米对应的像素数
        // }
        for(int i = 0; i < MT9V03X_H;i ++){
            temp = correct_left_border(leftline[i], i);
            trackline[i] = 
                (temp > 2 && temp < MT9V03X_W ) ? 
                (temp) :
                (
                    ((leftline[i]) - DEFAULT_SHIFT) < 2 ? 0 : (int16)(leftline[i] - DEFAULT_SHIFT)
                );
        }
    }
    if(track_type == TRACK_RIGHT){
        // for(int i = 0; i < MT9V03X_H;i ++){
        //     trackline[i] = ((rightline[i]) - (0.2 * PIX_PER_METER)) < 2 ? 0 : (int16)(rightline[i] - 0.2 * PIX_PER_METER);//循左线，右线应向左侧偏移
        // }
        for(int i = 0; i < MT9V03X_H;i ++){
            temp = correct_right_border(rightline[i], i);
            trackline[i] = 
                (temp > 2 && temp < MT9V03X_W ) ? 
                (temp) :
                (
                    ((rightline[i]) - DEFAULT_SHIFT) < 2 ? 0 : (int16)(rightline[i] - DEFAULT_SHIFT)
                );
        }
    }
}
//选择如何循线，大家可以自由发挥
void choose_tracktype(enum track_type_e type){
    track_type = type;
    switch_trackline();
}