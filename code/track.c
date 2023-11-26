#include "zf_common_headfile.h"

int16 trackline[MT9V03X_H];//������
enum track_type_e track_type = TRACK_MID;//Ĭ��ѭ����
//�����߸�ֵ��ѭ��������
void switch_trackline(void){
    if(track_type == TRACK_MID){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = centerline[i];//ѭ����
        }
    }
    if(track_type == TRACK_LEFT){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = (leftline[i] + PIX_PER_METER) > 187 ? 187 : (int16)(leftline[i] + 0.2 * PIX_PER_METER);//ѭ���ߣ�����Ӧ���Ҳ�ƫ�Ƶ�·���һ�룬��0.2�׶�Ӧ��������
        }
    }
    if(track_type == TRACK_RIGHT){
        for(int i = 0; i < MT9V03X_H;i ++){
            trackline[i] = ((rightline[i]) - PIX_PER_METER) < 0 ? 0 : (int16)(rightline[i] - 0.2 * PIX_PER_METER);//ѭ���ߣ�����Ӧ�����ƫ��
        }
    }
}
//ѡ�����ѭ�ߣ���ҿ������ɷ���
void choose_tracktype(void){

}