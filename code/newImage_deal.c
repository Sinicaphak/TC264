#include "zf_common_headfile.h"

float thres = 80;//80
uint8 thres0 = 80;//80
uint8 thres1 = 80;//80
float block_size = 5;
float clip_value = 2;
float pixel_per_meter = 102;
float sample_dist = 0.02;
///////////////// 修改 //////////////////////
// float begin_x = 14;
// int begin_y = 80;
float begin_x = 4;
int begin_y = 114;
///////////////// 修改结束 //////////////////////
float line_blur_kernel = 7;
float angle_dist = 0.20;
float far_rate = 0.5;
//float aim_distance = 0.56;
boolean adc_cross = false;



float L_ROW20_Half_WIDTH = 9;
float R_ROW20_Half_WIDTH = 9;
float ROAD_WIDTH_K = 35;

// 原图左右边线
int ipts0[POINTS_MAX_LEN][2] = {0};
int ipts1[POINTS_MAX_LEN][2] = {0};
int ipts0_num = 0, ipts1_num = 0;

// 逆透视左右边线
int rpts0[POINTS_MAX_LEN][2] = {0};
int rpts1[POINTS_MAX_LEN][2] = {0};
int rpts0_num = 0, rpts1_num = 0;

// 左右边线+滤波
float rpts0b[POINTS_MAX_LEN][2] = {0};
float rpts1b[POINTS_MAX_LEN][2] = {0};
int rpts0b_num = 0, rpts1b_num = 0;

// 左右边线+等距采样
float rpts0s[POINTS_MAX_LEN][2] = {0};
float rpts1s[POINTS_MAX_LEN][2] = {0};
int rpts0s_num = 0, rpts1s_num = 0;

// 左右边线局部角度变化率
float rpts0a[POINTS_MAX_LEN] = {0};
float rpts1a[POINTS_MAX_LEN] = {0};
int rpts0a_num = 0, rpts1a_num = 0;

// 左右边线局部角度变化率+非极大抑制
float rpts0an[POINTS_MAX_LEN] = {0};
float rpts1an[POINTS_MAX_LEN] = {0};
int rpts0an_num = 0, rpts1an_num = 0;

//// 左/右中线
float rptsc0[POINTS_MAX_LEN][2] = {0};//跟踪左线得到的中线
float rptsc1[POINTS_MAX_LEN][2] = {0};//跟踪右线得到的中线
float rptscm[POINTS_MAX_LEN][2] = {0};//左右线中值中线
int rptsc0_num = 0, rptsc1_num = 0;
int rptscm_num = 0;

// 归一化中线
float rptsn[POINTS_MAX_LEN][2] = {0};
int rptsn_num = 0;

// Y角点
int Ypt0_rpts0s_id = 0, Ypt1_rpts1s_id = 0;
boolean Ypt0_found = false, Ypt1_found = false;

// L角点
int Lpt0_rpts0s_id = 0, Lpt1_rpts1s_id = 0;
boolean Lpt0_found = false, Lpt1_found = false;

// 长直道
float straight0_num = 0, straight1_num = 0;
boolean is_straight0, is_straight1;

// 弯道
//boolean is_turn0, is_turn1;

// 当前巡线模式
enum track_type_e track_type = TRACK_MID;

image_t img_raw = DEF_IMAGE(mt9v03x_image, MT9V03X_H, MT9V03X_W);
//float garage_begin_y = 35;
uint8 init_thres = 140;

int no_found0 = 0;
int no_found1 = 0;
boolean Found0 = false;
boolean Found1 = false;


float Ypt0_conf, Ypt1_conf = 0;//Y角点阈值 
float Lpt0_conf, Lpt1_conf = 0;//L角点阈值 
float Ypt_dn, Ypt_dwn = 0;
float Lpt_dn, Lpt_dwn = 0;

void image_process(void){
    thres0 = init_thres;
    thres1 = init_thres;

    // 原图找左右边线
    int x1 = img_raw.width / 2 - begin_x,
        y1 = begin_y;
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    for (; x1 > 1; x1--) {
        if (AT_IMAGE(&img_raw, x1 - 1, y1) < thres0) {
            break;
        }
    }
    if (AT_IMAGE(&img_raw, x1, y1) >= thres0){
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, x1, y1, ipts0, &ipts0_num);
        Found0 = true;
        no_found0 = 0;
    } else {
        ipts0_num = 0;
        no_found0 ++;
        Found0 = false;
        ///////////////// 修改 //////////////////////
        tft180_show_string(COLUMN_LEFT_X, (uint16)(7*8), "NOT FOUND0");
        ///////////////// 修改结束 //////////////////////
    }

    int x2 = img_raw.width / 2 + begin_x, y2 = begin_y;
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    for (; x2 < img_raw.width - 1; x2++) {
        if (AT_IMAGE(&img_raw, x2 + 1, y2) < thres1) {
            break;
        }
    }
    if (AT_IMAGE(&img_raw, x2, y2) >= thres1){
        findline_righthand_adaptive(&img_raw, block_size, clip_value, x2, y2, ipts1, &ipts1_num);
        Found1 = true;
        no_found1 = 0;
    } else {
        ipts1_num = 0;
        no_found1 ++;
        Found1 = false;
        ///////////////// 修改 //////////////////////
        tft180_show_string(COLUMN_LEFT_X, (uint16)(9*8), "NOT FOUND1");
        ///////////////// 修改结束 //////////////////////
    }

    
    // //边线透视变换
    // Pespective(ipts0, ipts0_num, rpts0);
    // rpts0_num = ipts0_num;
    // Pespective(ipts1, ipts1_num, rpts1);
    // rpts1_num = ipts1_num;
    // // 边线滤波
    // blur_points(rpts0, rpts0_num, rpts0b, (int) round(line_blur_kernel));
    // rpts0b_num = rpts0_num;
    // blur_points(rpts1, rpts1_num, rpts1b, (int) round(line_blur_kernel));
    // rpts1b_num = rpts1_num;

    // // 边线等距采样
    // rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    // resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    // rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    // resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);
    // //7.ms

    // // 边线局部角度变化率
    // local_angle_points(rpts0s, rpts0s_num, rpts0a, 10);
    // rpts0a_num = rpts0s_num;
    // local_angle_points(rpts1s, rpts1s_num, rpts1a, 10);
    // rpts1a_num = rpts1s_num;
    // //5.ms

    // // 角度变化率非极大抑制
    // nms_angle(rpts0a, rpts0a_num, rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    // rpts0an_num = rpts0a_num;
    // nms_angle(rpts1a, rpts1a_num, rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    // rpts1an_num = rpts1a_num;

    // track_leftline(rpts0s, rpts0s_num, rptsc0, (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    // rptsc0_num = rpts0s_num;
    // track_rightline(rpts1s, rpts1s_num, rptsc1, (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    // rptsc1_num = rpts1s_num;

    // track_midline(rpts0s, rpts0s_num, rpts1s, rpts1s_num, rptscm);
    // rptscm_num = MIN(rpts0s_num, rpts1s_num);

    // straight0_num = check_straight(rpts0s, rpts0s_num);
    // straight1_num = check_straight(rpts1s, rpts1s_num);
}

uint8 jump_point = 5;
float k_thres = 5;
float fir_k = 0;
float check_straight(float pts_in[][2], int num)
{
    uint8 straight_num = jump_point + 1;
    uint8 no_s = 0;
    float sec_k = 0;
//    float last_k = 0;
    float dx1 = 10;
    float dn1 = sqrtf(dx1 * dx1);
    float dx2 = pts_in[jump_point][0] - pts_in[0][0];
    float dy2 = pts_in[jump_point][1] - pts_in[0][1];
    float dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
    float c1 = dx1 / dn1;
    float c2 = dx2 / dn2;
    float s2 = dy2 / dn2;
    fir_k = 180*atan2f(c1 * s2, c2 * c1)/PI;

    for (int i = jump_point+1; i < num; i++) {
         dx2 = pts_in[i][0] - pts_in[0][0];
         dy2 = pts_in[i][1] - pts_in[0][1];
         dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
         c2 = dx2 / dn2;
         s2 = dy2 / dn2;
         sec_k = 180*atan2f(c1 * s2, c2 * c1)/PI;
         if (fabs(sec_k-fir_k)<k_thres) {
             straight_num++;
             no_s = 0;
        }else {
            no_s++;
        }
         if (no_s>2) {
             straight_num = straight_num - no_s;
            break;
        }
    }

    return straight_num;
}

uint8 left_thres(void)
{
    float contrast = 0, max_contrast = -1;
    uint8 max_contrast_thres = 0;
    int jump_num = 2; //中间隔两个点
    float a, b;
    for (int i = MT9V03X_W/2; i > jump_num; i--) {
        a = AT_IMAGE(&img_raw, i, begin_y);
        b = AT_IMAGE(&img_raw, i-jump_num-1, begin_y);
        contrast = fabs(a-b)*100/(a+b);
        if (contrast > max_contrast) {
            max_contrast = contrast;
            max_contrast_thres = (a+b)/2;
        }
    }
    return max_contrast_thres;
}

uint8 right_thres(void)
{
    int jump_num = 2;
    float contrast = 0, max_contrast = -1;
    uint8 max_contrast_thres = 0;
    float a, b;
    for (int i = MT9V03X_W/2; i < MT9V03X_W - jump_num - 1; i++) {
        a = AT_IMAGE(&img_raw, i, begin_y);
        b = AT_IMAGE(&img_raw, i+jump_num+1, begin_y);
        contrast = fabs(a-b)*100/(a+b);
        if (contrast > max_contrast) {
            max_contrast = contrast;
            max_contrast_thres = (a+b)/2;
        }
    }
    return max_contrast_thres;
}


#define a11 (2.33145776e+00)
#define a12 (3.07998761e+00)
#define a13 (-7.70240636e+01)
#define a21 (1.38992993e-01)
#define a22 (5.29631665e+00)
#define a23 (-8.33813133e+01)
#define a31 (1.47320530e-03)
#define a32 (3.89122946e-02)
#define a33 (1.00000000e+00)
//#define a11 (1.90028008e+00)
//#define a12 (3.04694624e+00)
//#define a13 (-5.98790267e+01)
//#define a21 (-3.73152807e-02)
//#define a22 (4.71172875e+00)
//#define a23 (-6.27237607e+01)
//#define a31 (-1.53876708e-03)
//#define a32 (3.91528504e-02)
//#define a33 (1.00000000e+00)
#define getx(u,v) (a11*(u)+a12*(v)+a13)
#define gety(u,v) (a21*(u)+a22*(v)+a23)
#define getw(u,v) (a31*(u)+a32*(v)+a33)

//[[ 2.33145776e+00  3.07998761e+00 -7.70240636e+01]
// [ 1.38992993e-01  5.29631665e+00 -8.33813133e+01]
// [ 1.47320530e-03  3.89122946e-02  1.00000000e+00]]

//[[ 1.90028008e+00  3.04694624e+00 -5.98790267e+01]
// [-3.73152807e-02  4.71172875e+00 -6.27237607e+01]
// [-1.53876708e-03  3.91528504e-02  1.00000000e+00]]



//带入提取出来的两条边线，得到透视变换后的两条边线
void Pespective(int pts_in[][2], int num, int pts_out[][2])
{
    float x, y, w;
    for (int16_t i = 0; i < num; i++)
    {
        x = getx(pts_in[i][0], pts_in[i][1]);
        y = gety(pts_in[i][0], pts_in[i][1]);
        w = getw(pts_in[i][0], pts_in[i][1]);
        pts_out[i][0] = x / w;
        pts_out[i][1] = y / w;
    }
}


//最小二乘法线性拟合直线
void Linear_Fitting(float pts_in[][2], int num, float pts_out[][2])
{
    double K=0,b=0,A=0,B=0,C=0,D=0;
    float dy = (begin_y-pts_in[num][1])/num;
    for(int i=0;i<num;i++)
    {
        A+=pts_in[i][0]*pts_in[i][1];
        B+=pts_in[i][0];
        C+=pts_in[i][1];
        D+=pts_in[i][0]*pts_in[i][0];
    }
    K=(num*A-B*C)/(num*D-B*B);
    b=C/num-K*B/num;
    /*将计算得到的直线参数通过指针传递到函数外部*/
    for (int i = 0;i < num; i++) {
        pts_out[i][1] = 80-dy*i;
        pts_out[i][0] = (pts_out[i][1]-b)/K;
    }

}




//float line_Standard_slope = 0;
//float slope_error = 100.;
//float line_Slope_L = 0.;
//float line_Slope_m_R = 0.;
//float line_Slope_m_L = 0.;
//float line_Slope_R = 0.;
//int Judge_line_points0(void)
//{
//    float line_begin_x,line_begin_y,line_next_x,line_next_y;
////    float line_Slope = 0.;
//    int line_points = 0;
//    int line_point,line_n;
//        line_begin_x = rpts0s[1][0];
//        line_begin_y = rpts0s[1][1];
//        line_next_x = rpts0s[5][0];
//        line_next_y = rpts0s[5][1];
//
//        line_Slope_m_L = (line_next_y-line_begin_y)/(line_next_x-line_begin_x);
//      for(line_point=0,line_n=6;line_n < rpts0s_num;line_n++)
//      {
//        line_next_x = rpts0s[line_n][0];
//        line_next_y = rpts0s[line_n][1];
//
//        line_Slope_L = (line_next_y-line_begin_y)/(line_next_x-line_begin_x);
//        if((line_Slope_L < (line_Slope_m_L+slope_error/100.)) && (line_Slope_L > (line_Slope_m_L-slope_error/100.))) line_points++;
//        else  break;
//      }
//    return (line_points);
//}
//int Judge_line_points1(void)
//{
//    float line_begin_x,line_begin_y,line_next_x,line_next_y;
////    float line_Slope = 0.;
//    int line_points = 0;
//    int line_point,line_n;
//    line_begin_x = rpts1s[1][0];
//    line_begin_y = rpts1s[1][1];
//    line_next_x = rpts1s[5][0];
//    line_next_y = rpts1s[5][1];
//
//    line_Slope_m_R = (line_next_y-line_begin_y)/(line_next_x-line_begin_x);
//   for(line_point=0,line_n=6;line_n <rpts1s_num; line_n++)
//   {
//     line_next_x = rpts1s[line_n][0];
//     line_next_y = rpts1s[line_n][1];
//
//     line_Slope_R = (line_next_y-line_begin_y)/(line_next_x-line_begin_x);
//     if((line_Slope_R < (line_Slope_m_R + slope_error/100.)) && (line_Slope_R > (line_Slope_m_R - slope_error/100.))) line_points++;
//     else  break;
//    }
//   return (line_points);
//}


/* 前进方向定义：
 *   0
 * 3   1
 *   2
 */
const int dir_front[4][2] = {{0,  -1},
                            {1,  0},
                            {0,  1},
                            {-1, 0}};
const int dir_frontleft[4][2] = {{-1, -1},
                                {1,  -1},
                                {1,  1},
                                {-1, 1}};
const int dir_frontright[4][2] = {{1,  -1},
                                 {1,  1},
                                 {-1, 1},
                                 {-1, -1}};

void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
//    zf_assert(num && *num >= 0);
//    zf_assert(block_size > 1 && block_size % 2 == 1);
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && half < x && x < img->width - half - 1 && half < y && y < img->height - half - 1 && turn < 4) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

//        int current_value = AT(img, x, y);
        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontleft_value = AT(img, x + dir_frontleft[dir][0], y + dir_frontleft[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 1) % 4;
            turn++;
        } else if (frontleft_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        } else {
            x += dir_frontleft[dir][0];
            y += dir_frontleft[dir][1];
            dir = (dir + 3) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        }
    }
    *num = step;
}
void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
//    zf_assert(num && *num >= 0);
//    zf_assert(block_size > 1 && block_size % 2 == 1);
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && 0 < x && x < img->width - 1 && 0 < y && y < img->height - 1 && turn < 4) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

//        int current_value = AT(img, x, y);
        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontright_value = AT(img, x + dir_frontright[dir][0], y + dir_frontright[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        } else {
            x += dir_frontright[dir][0];
            y += dir_frontright[dir][1];
            dir = (dir + 1) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        }
    }
    *num = step;
}

// 点集三角滤波
void blur_points(int pts_in[][2], int num, float pts_out[][2], int kernel) {
    zf_assert(kernel % 2 == 1);
    int half = kernel / 2;
    for (int i = 0; i < num; i++)
    {
        pts_out[i][0] = pts_out[i][1] = 0;
        for (int j = -half; j <= half; j++)
        {
            pts_out[i][0] += pts_in[clip(i + j, 0, num - 1)][0] * (half + 1 - abs(j));
            pts_out[i][1] += pts_in[clip(i + j, 0, num - 1)][1] * (half + 1 - abs(j));
        }
        pts_out[i][0] /= (2 * half + 2) * (half + 1) / 2;
        pts_out[i][1] /= (2 * half + 2) * (half + 1) / 2;
    }
}

// 点集等距采样
void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist) {
    if (num1 < 0) {
        *num2 = 0;
        return;
    }
    pts_out[0][0] = pts_in[0][0];
    pts_out[0][1] = pts_in[0][1];
    int len = 1;
    for (int i = 0; i < num1 - 1 && len < *num2; i++) {
        float x0 = pts_in[i][0];
        float y0 = pts_in[i][1];
        float x1 = pts_in[i + 1][0];
        float y1 = pts_in[i + 1][1];

        do {
            float x = pts_out[len - 1][0];
            float y = pts_out[len - 1][1];

            float dx0 = x0 - x;
            float dy0 = y0 - y;
            float dx1 = x1 - x;
            float dy1 = y1 - y;

            float dist0 = sqrt(dx0 * dx0 + dy0 * dy0);
            float dist1 = sqrt(dx1 * dx1 + dy1 * dy1);

            float r0 = (dist1 - dist) / (dist1 - dist0);
            float r1 = 1 - r0;

            if (r0 < 0 || r1 < 0) break;
            x0 = x0 * r0 + x1 * r1;
            y0 = y0 * r0 + y1 * r1;
            pts_out[len][0] = x0;
            pts_out[len][1] = y0;
            len++;
        } while (len < *num2);

    }
    *num2 = len;
}

// 点集局部角度变化率
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist) {
    for (int i = 0; i < num; i++) {
        if (i <= 0 || i >= num - 1) {
            angle_out[i] = 0;
            continue;
        }
        float dx1 = pts_in[i][0] - pts_in[clip(i - dist, 0, num - 1)][0];
        float dy1 = pts_in[i][1] - pts_in[clip(i - dist, 0, num - 1)][1];
        float dn1 = sqrtf(dx1 * dx1 + dy1 * dy1);
        float dx2 = pts_in[clip(i + dist, 0, num - 1)][0] - pts_in[i][0];
        float dy2 = pts_in[clip(i + dist, 0, num - 1)][1] - pts_in[i][1];
        float dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        float c1 = dx1 / dn1;
        float s1 = dy1 / dn1;
        float c2 = dx2 / dn2;
        float s2 = dy2 / dn2;
        angle_out[i] = atan2f(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1);//c1 * s2 - c2 * s1, c2 = sin(2-1);c2 * c1 + s2 * s1 = cos(2-1);arctan(tanx) = x;
    }
}



// 角度变化率非极大抑制
void nms_angle(float angle_in[], int num, float angle_out[], int kernel) {
    zf_assert(kernel % 2 == 1);
    int half = kernel / 2;
    for (int i = 0; i < num; i++) {
        angle_out[i] = angle_in[i];
        for (int j = -half; j <= half; j++) {
            if (fabs(angle_in[clip(i + j, 0, num - 1)]) > fabs(angle_out[i])) {
                angle_out[i] = 0;
                break;
            }
        }
    }
}


// 左边线跟踪中线
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;
    }
}

// 右边线跟踪中线
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}

//左右边线计数中线
void track_midline(float pts_in1[][2], int num1, float pts_in2[][2], int num2, float pts_out[][2]) {
    int num = MIN(num1, num2);
    for (int i = 0; i < num; i++) {
        pts_out[i][0] = (pts_in1[i][0] + pts_in2[i][0]) / 2;
        pts_out[i][1] = (pts_in1[i][1] + pts_in2[i][1]) / 2;
    }
}

// 左边线跟踪中线
void track_leftline2(float pts_in[][2], int num, float pts_out[][2], int approx_num) {
    for (int i = 0; i < num; i++) {
        float dist = (ROAD_WIDTH_K/100) * pts_in[i][1] + L_ROW20_Half_WIDTH;
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;
    }
}

// 右边线跟踪中线
void track_rightline2(float pts_in[][2], int num, float pts_out[][2], int approx_num) {
    for (int i = 0; i < num; i++) {
        float dist = (ROAD_WIDTH_K/100) * pts_in[i][1] + R_ROW20_Half_WIDTH;
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}

#if 0

uint8 OTSU_Plus(uint8 *image, uint16 col, uint16 row)   //注意计算阈值的一定要是原图像
{
   #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数

        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[j];       //灰度值总和
        }

    //计算每个像素值的点在整幅图像中的比例

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;


        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {

                w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
                u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;

                u0 = u0tmp / w0;              //背景平均灰度
                u1 = u1tmp / w1;              //前景平均灰度
                u = u0tmp + u1tmp;            //全局平均灰度
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }

         }

    return threshold;

}



//最佳迭代法阈值计算
uint8 Best_iteration(uint8* image, uint16 width, uint16 height)
{
    int X, Iter = 0;
    int j;
    uint16 HistGram[256] = {0};
    int MeanValueOne, MeanValueTwo, SumOne, SumTwo, SumIntegralOne, SumIntegralTwo;
    int MinValue, MaxValue;
    uint8 Threshold, NewThreshold;
          for (j = 0; j < width; j++)
          {
                if(image[j] == 0) image[j] = 1;
          }
          HistGram[image[j]]++;
    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ;

    if (MaxValue == MinValue) return MaxValue;          // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue) return MinValue;      // 图像中只有二个颜色

    Threshold = MinValue;
    NewThreshold = (MaxValue + MinValue) >> 1;
    while (Threshold != NewThreshold)    // 当前后两次迭代的获得阈值相同时，结束迭代
    {
        SumOne = 0; SumIntegralOne = 0;
        SumTwo = 0; SumIntegralTwo = 0;
        Threshold = NewThreshold;
        for (X = MinValue; X <= Threshold; X++)         //根据阈值将图像分割成目标和背景两部分，求出两部分的平均灰度值
        {
            SumIntegralOne += HistGram[X] * X;
            SumOne += HistGram[X];
        }
        MeanValueOne = SumIntegralOne / SumOne;
        for (X = Threshold + 1; X <= MaxValue; X++)
        {
            SumIntegralTwo += HistGram[X] * X;
            SumTwo += HistGram[X];
        }
        MeanValueTwo = SumIntegralTwo / SumTwo;
        NewThreshold = (MeanValueOne + MeanValueTwo) >> 1;       //求出新的阈值
        Iter++;
        if (Iter >= 1000) return -1;
    }
    return Threshold;
}
#endif

uint8 Image_Use[MT9V03X_H][MT9V03X_W];

void Image_array_copy(void)
{
    volatile uint16 num;
    for (num = 0; num < MT9V03X_H; num++)
    {
        memcpy(Image_Use[num], mt9v03x_image[num], MT9V03X_W); //将缓冲区的图片拷贝到显示区
    }
}

void Image_Binary(uint16 Height, uint16 Width, uint8 Threshold)
{
    for (uint8 i = Height-2; i>0; i--)
    {
        for (uint8 j = 1; j < Width-1; j++)
        {
            if (Image_Use[i][j] < Threshold)
                Image_Use[i][j] = 0;
            else Image_Use[i][j] = 255;
        }

    }
}
//-------------------------------------------------------------------------------------------------------------------
//大津法阈值
//-------------------------------------------------------------------------------------------------------------------
uint8 OTSU_Threshold(uint8 *image, uint16 col, uint16 row)   //注意计算阈值的一定要是原图像
{
   #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale] = {0};
    float pixelPro[GrayScale] = {0};
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针

    uint32 gray_sum = 0;
    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
        }
    }

    //计算每个像素值的点在整幅图像中的比例

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
                w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
                u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;

                u0 = u0tmp / w0;              //背景平均灰度
                u1 = u1tmp / w1;              //前景平均灰度
                u = u0tmp + u1tmp;            //全局平均灰度
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }

         }

    return threshold;
}


int clip(int x, int low, int up) {
    return x > up ? up : x < low ? low : x;
}

float fclip(float x, float low, float up) {
    return x > up ? up : x < low ? low : x;
}






