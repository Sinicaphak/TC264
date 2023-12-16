//ifdef
#ifndef _FUN_H_
#define _FUN_H_

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 128
#define MATRIX_SIZE   10

#define RIGHTLINE_KF 0.60
#define RIGHTLINE_B 25


#define LEFTLINE_KF 0.60
#define LEFTLINE_B 15


// 将input限制在 [ -limit , limit ]
double limit_amplitude_absolute(double input, double limit);
// 将input限制在 [ lower_limit , upper_limit ]
double limit_amplitude_upper_lower(double input, double upper_limit, double lower_limit);
// 求平均值
double average(double *history, int length);
// 取中位数
double median(double *history, int length);
// 将数组后移一位
void move_array_back(double *history, int length);
// 将数组后移一位, input插入到第一位
void move_back_and_insert(double *history, int length, double input);
// 滑动窗口滤波: 将数组后移一位, input插入到第一位, 然后求平均值, input大于阈值时返回均值
double sliding_window_filter(double *history, int length, double input, double threshold);
// 差比和
double diff(double l, double r);
// 平滑滤波: 将数组后移一位, input插入到第一位, 然后求平均值
double smooth(double *history, int length, double input);
// 求车轮转速 = 编码器脉冲数 * 减速比 / 每圈脉冲数
double calculate_speed(int pluse);

void draw_matrix(void);

int correct_right_border(int x, int y);
// endif
#endif
