#include "zf_common_headfile.h"

int16 trackline[MT9V03X_H];//跟踪线
enum track_type_e track_type = TRACK_MID;//默认循中线
//将边线赋值给循迹跟踪线
void switch_trackline(void){
    if(track_type == TRACK_MID){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = centerline[i];//循中线
        }
    }
    if(track_type == TRACK_LEFT){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = (leftline[i] + PIX_PER_METER) > 187 ? 187 : (int16)(leftline[i] + 0.2 * PIX_PER_METER);//循左线，左线应向右侧偏移道路宽度一半，即0.2米对应的像素数
        }
    }
    if(track_type == TRACK_RIGHT){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = ((rightline[i]) - PIX_PER_METER) < 0 ? 0 : (int16)(rightline[i] - 0.2 * PIX_PER_METER);//循左线，右线应向左侧偏移
        }
    }
}
//选择如何循线，大家可以自由发挥
void choose_tracktype(void){

}