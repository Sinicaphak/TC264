//ifdef
#ifndef _FUN_H_
#define _FUN_H_


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
// ��main�м��д���ɼ���������
void process_data(void);
// ��Ⱥ�
double diff(double l, double r);
// ƽ���˲�: ���������һλ, input���뵽��һλ, Ȼ����ƽ��ֵ
double smooth(double *history, int length, double input);
// ����ת�� = ������������ * ���ٱ� / ÿȦ������
double calculate_speed(int pluse);

// endif
#endif
