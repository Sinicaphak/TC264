//ifndef
#ifndef _NEWIMAGE_DEAL_H_
#define _NEWIMAGE_DEAL_H_

#define ROAD_WIDTH      (0.4)
#define POINTS_MAX_LEN  (MT9V03X_H)
//从底层zf_device_mt9v03x_dvp.h中摘抄 
//#define MT9V03X_DVP_W               160                                             // 图像宽度  范围1-752
//#define MT9V03X_DVP_H               100                                             // 图像高度 范围1-480
//#define MT9V03X_IMAGE_SIZE_DVP      (MT9V03X_DVP_W*MT9V03X_DVP_H)

#define FAR_POINTS_MAX_LEN  (POINTS_MAX_LEN)

#define false 0
#define true  1
#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


extern float thres;
extern uint8 thres0;//90
extern uint8 thres1;//90
extern float block_size;
extern float clip_value;
extern float begin_x;
extern int begin_y;
extern float line_blur_kernel;
extern float pixel_per_meter;
extern float sample_dist;
extern float angle_dist;
extern float far_rate;
//extern float aim_distance;
extern boolean adc_cross;


// 原图左右边线
extern int ipts0[POINTS_MAX_LEN][2];
extern int ipts1[POINTS_MAX_LEN][2];
extern int ipts0_num, ipts1_num;

extern int rpts0[POINTS_MAX_LEN][2];
extern int rpts1[POINTS_MAX_LEN][2];
extern int rpts0_num, rpts1_num;
// 变换后左右边线+滤波
extern float rpts0b[POINTS_MAX_LEN][2];
extern float rpts1b[POINTS_MAX_LEN][2];
extern int rpts0b_num, rpts1b_num;
// 变换后左右边线+等距采样
extern float rpts0s[POINTS_MAX_LEN][2];
extern float rpts1s[POINTS_MAX_LEN][2];
extern int rpts0s_num, rpts1s_num;
// 左右边线局部角度变化率
extern float rpts0a[POINTS_MAX_LEN];
extern float rpts1a[POINTS_MAX_LEN];
extern int rpts0a_num, rpts1a_num;
// 左右边线局部角度变化率+非极大抑制
extern float rpts0an[POINTS_MAX_LEN];
extern float rpts1an[POINTS_MAX_LEN];
extern int rpts0an_num, rpts1an_num;
// 左/右中线
extern float rptsc0[POINTS_MAX_LEN][2];//跟踪左线得到的中线
extern float rptsc1[POINTS_MAX_LEN][2];//跟踪右线得到的中线
extern float rptscm[POINTS_MAX_LEN][2];//左右线中值中线
extern int rptsc0_num, rptsc1_num;
extern int rptscm_num;

extern uint8 show_L;
extern uint8 show_Y;

// 中线
//extern float (*rpts)[2];
//extern int rpts_num;
// 归一化中线
extern float rptsn[POINTS_MAX_LEN][2];
extern int rptsn_num;

// Y角点
extern int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
extern boolean Ypt0_found, Ypt1_found;

// L角点
extern int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
extern boolean Lpt0_found, Lpt1_found;

// 长直道
extern float straight0_num, straight1_num;
extern boolean is_straight0, is_straight1;

// 弯道
//extern boolean is_turn0, is_turn1;

extern float ROW80_Half_WIDTH;
extern float R_ROW20_Half_WIDTH;
extern float L_ROW20_Half_WIDTH;
extern float ROAD_WIDTH_K;

typedef struct image {
    uint8_t *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} image_t;

//定义巡线模式枚举类型
enum track_type_e {
    TRACK_LEFT,//沿左边线
    TRACK_RIGHT,//沿右边线
    TRACK_MID,//沿中线
};

//定义当前循线模式
extern enum track_type_e track_type;

extern image_t img_raw;
//extern float garage_begin_y;
extern uint8 init_thres;
extern boolean Found0,Found1;

extern float Ypt0_conf, Ypt1_conf;
extern float Lpt0_conf, Lpt1_conf;
extern float Ypt_dn, Ypt_dwn;
extern float Lpt_dn, Lpt_dwn;

extern uint8 jump_point;
extern float k_thres;
extern float fir_k;
extern uint8 Image_Use[MT9V03X_H][MT9V03X_W];

#define AT_IMAGE(img, x, y)          ((img)->data[(y)*(img)->step+(x)])
#define AT_IMAGE_CLIP(img, x, y)     AT_IMAGE(img, clip(x, 0, (img)->width-1), clip(y, 0, (img)->height-1))
#define AT                  AT_IMAGE
#define AT_CLIP(img, x, y)  AT_IMAGE((img), clip((x), 0, (img)->width-1), clip((y), 0, (img)->height-1));

#define DEF_IMAGE(ptr, w, h)         {.data=ptr, .width=w, .height=h, .step=w}
#define ROI_IMAGE(img, x1, y1, w, h) {.data=&AT_IMAGE(img, x1, y1), .width=w, .height=h, .step=img.width}

void image_process(void);
//uint8 OTSU_Plus(uint8 *image, uint16 col, uint16 row);
uint8 OTSU_Threshold(uint8 *image, uint16 col, uint16 row);
//uint8 Best_iteration(uint8* image, uint16 width, uint16 height);
void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);
void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);
uint8 left_thres(void);
uint8 right_thres(void);
void blur_points(int pts_in[][2], int num, float pts_out[][2], int kernel);
void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist);
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);
void nms_angle(float angle_in[], int num, float angle_out[], int kernel) ;
void Linear_Fitting(float pts_in[][2], int num, float pts_out[][2]);
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);
void track_leftline2(float pts_in[][2], int num, float pts_out[][2], int approx_num);
void track_rightline2(float pts_in[][2], int num, float pts_out[][2], int approx_num);
void track_midline(float pts_in1[][2], int num1, float pts_in2[][2], int num2, float pts_out[][2]);
float check_straight(float pts_in[][2], int num);
void Pespective(int pts_in[][2], int num, int pts_out[][2]);
void Image_array_copy(void);
void Image_Binary(uint16 Height, uint16 Width, uint8 Threshold);

//int Judge_line_points0(void);
//int Judge_line_points1(void);
int clip(int x, int low, int up);
float fclip(float x, float low, float up);

//endif
#endif