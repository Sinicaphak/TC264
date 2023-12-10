#include "zf_common_headfile.h"

int16 centerline[MT9V03X_H];
int16 leftline[MT9V03X_H];
int16 rightline[MT9V03X_H];
uint8 leftline_num;//���ߵ�����
uint8 rightline_num;//���ߵ�����
/* �޸� */
//ԭ // int16 SAR_THRE = 17;//��Ⱥ���ֵ
int16 SAR_THRE = 17;//��Ⱥ���ֵ
/* �޸Ľ��� */
uint8 PIX_PER_METER = 20;//ÿ�׵�������

//����Ѱ�ұ߽��
void image_boundary_process(void){
    uint8 row;//��
    //uint8 col = MT9V03X_W/2;//��
    uint8 start_col = MT9V03X_W / 2;//��������������,Ĭ��ΪMT9V03X_W / 2
    //����֮ǰ�ļ���
    leftline_num = 0;
    rightline_num = 0;
    for(row = MT9V03X_H - 1; row >= 1; row--){
    //ѡ����һ�е��е���Ϊ��һ�м�����ʼ�㣬��ʡ�ٶȣ�ͬʱ��ֹ������������߾������뻭��һ��
        if(row != MT9V03X_H - 1){
            start_col = (uint8)(0.4 * centerline[row] + 0.3 * start_col + 0.1 * MT9V03X_W);//һ�׵�ͨ�˲�����ֹ�������Ӱ����һ�е���ʼ��
        }
        else if(row == MT9V03X_H - 1){
            start_col = MT9V03X_W / 2;
        }
    //��������Ⱥ�
        difsum_left(row,start_col);
        difsum_right(row,start_col);
        centerline[row] = 0.5 * (rightline[row] + leftline[row]);
    }
}

//��Ⱥ�Ѱ�����߽��
void difsum_left(uint8 y,uint8 x){
    float sum,dif,sar;//�ͣ����
    uint8 col;//��
    uint8 mov = 2;//ÿ���������ƶ���,Ĭ��Ϊ2�����Ը��ݻ���ֱ��ʵ���
    //�����x�е���߽�
    leftline[y] = 0;//δ�ҵ���߽�ʱ���Ϊ0
    for(col = x; col >= mov + 1; col -= mov){
            dif = (float)((mt9v03x_image[y][col] - mt9v03x_image[y][col - mov - 1])<<8);//����8λ����256���ɱ��⸡�����ˣ��ӿ��ٶ�
            sum = (float)((mt9v03x_image[y][col] + mt9v03x_image[y][col - mov - 1]));
            sar = fabs(dif / sum);//��ȡ��Ⱥ�
        if(sar > SAR_THRE){//��Ⱥʹ�����ֵ������ǳɫͻ��
            leftline[y] = (int16)(col - mov) + LEFT_LINE_SHIFT;
            leftline_num ++;//���ߵ����+
            break;//�ҵ��߽���˳�
        }
    }
}
//��Ⱥ�Ѱ���Ҳ�߽��
void difsum_right(uint8 y,uint8 x){
    float sum,dif,sar;//�ͣ����
    uint8 col;//��
    uint8 mov = 2;//ÿ���������ƶ���,Ĭ��Ϊ2�����Ը��ݻ���ֱ��ʵ���
    //�����x�е���߽�
    rightline[y] = MT9V03X_W - 1;//δ�ҵ��ұ߽�ʱ���Ϊ187
    for(col = x; col <= MT9V03X_W - mov - 1; col += mov) {
        dif = (float)((mt9v03x_image[y][col] - mt9v03x_image[y][col + mov + 1])<<8);//����8λ����256���ɱ��⸡�����ˣ��ӿ��ٶ�
        sum = (float)((mt9v03x_image[y][col] + mt9v03x_image[y][col + mov + 1]));
        sar = fabs(dif / sum);//��ȡ��Ⱥ�
        if(sar > SAR_THRE){//��Ⱥʹ�����ֵ������ǳɫͻ��
            rightline[y] = (int16)(col + mov) - RIGHT_LINE_SHIFT;
            rightline_num ++;//���ߵ����+
            break;//�ҵ��߽���˳�
        }
    }
}




