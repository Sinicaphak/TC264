//
// Created by RUPC on 2022/9/20.
//
#include "zf_common_headfile.h"

#define RESULT_ROW MT9V03X_H//结果图行列
#define RESULT_COL MT9V03X_W
#define         USED_ROW                MT9V03X_H  //用于透视图的行列
#define         USED_COL                MT9V03X_W
#define PER_IMG     mt9v03x_image//SimBinImage:用于透视变换的图像
#define ImageUsed   *PerImg_ip//*PerImg_ip定义使用的图像，ImageUsed为用于巡线和识别的图像
uint8_t *PerImg_ip[RESULT_ROW][RESULT_COL];

double change_un_Mat[3][3] ={{0.501336,-0.414485,9.621704},{0.005902,0.040352,4.179728},{-0.000084,-0.004327,0.603103}};


void ImagePerspective_Init(void) {

    static uint8_t BlackColor = 0;
    for (int i = 0; i < RESULT_COL ;i++) {
        for (int j = 0; j < RESULT_ROW ;j++) {
            int local_x = (int) ((change_un_Mat[0][0] * i
                    + change_un_Mat[0][1] * j + change_un_Mat[0][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            int local_y = (int) ((change_un_Mat[1][0] * i
                    + change_un_Mat[1][1] * j + change_un_Mat[1][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            if (local_x
                    >= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL){
                PerImg_ip[j][i] = &PER_IMG[local_y][local_x];
            }
            else {
                PerImg_ip[j][i] = &BlackColor;          //&PER_IMG[0][0];
            }

        }
    }

}


/*完成摄像头初始化后，调用一次ImagePerspective_Init，此后，直接调用ImageUsed   即为透视结果*/