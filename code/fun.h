//ifdef
#ifndef _FUN_H_
#define _FUN_H_

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 128
#define MATRIX_SIZE   10

#define RIGHTLINE_KF 0.50
#define RIGHTLINE_B 25


#define LEFTLINE_KF 0.60
#define LEFTLINE_B 15

#define HALF_WIDTH MT9V03X_W / 2

// ��input������ [ -limit , limit ]
double limit_amplitude_absolute(double input, double limit);
// ��input������ [ lower_limit , upper_limit ]
double limit_amplitude_upper_lower(double input, double upper_limit, double lower_limit);
// ��ƽ��ֵ
double average(double *history, int length);
// ȡ��λ��
double median(double *history, int length);
// ���������һλ
void move_array_back(double *history, int length);
// ���������һλ, input���뵽��һλ
void move_back_and_insert(double *history, int length, double input);
// ���������˲�: ���������һλ, input���뵽��һλ, Ȼ����ƽ��ֵ, input������ֵʱ���ؾ�ֵ
double sliding_window_filter(double *history, int length, double input, double threshold);
// ��Ⱥ�
double diff(double l, double r);
// ƽ���˲�: ���������һλ, input���뵽��һλ, Ȼ����ƽ��ֵ
double smooth(double *history, int length, double input);
// ����ת�� = ������������ * ���ٱ� / ÿȦ������
double calculate_speed(int pluse);

void draw_matrix(void);
int clap(int input, int up, int down);

int correct_right_border(int x, int y);
/**
 * @brief ����: ����Ļ��������Ļ���油
 * @param begin_y: ��ʼ���ߵ�y����
 * @param end_y: �������ߵ�y����
 * @param line_need_fix: ��Ҫ���ߵı���
 */
void fix_line(int begin_y, int end_y, int end_x, int begin_x, int line_need_fix[MT9V03X_H], bool is_left);
/**
 * @brief ��ӡ��־
 */
void self_log(const char *str);


#define fix_line_spot_cross(begin_y, end_y, line_need_fix, is_left) fix_line(begin_y, end_y, line_need_fix[begin_y], line_need_fix[end_y], line_need_fix, is_left);
#define fix_line_in_cross(begin_y, line_need_fix, is_left) fix_line(begin_y, BUTTON, LEFT_LINE_BOUNDARY, RIGHT_LINE_BOUNDARY, line_need_fix, is_left);
// endif
#endif
