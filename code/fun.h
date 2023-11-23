//ifdef
#ifndef _FUN_H_
#define _FUN_H_


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
// 在main中集中处理采集到的数据
void process_data(void);
// 差比和
double diff(double l, double r);
// 平滑滤波: 将数组后移一位, input插入到第一位, 然后求平均值
double smooth(double *history, int length, double input);
// 求车轮转速 = 编码器脉冲数 * 减速比 / 每圈脉冲数
double calculate_speed(int pluse);

// endif
#endif
