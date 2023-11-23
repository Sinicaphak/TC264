#include "zf_common_headfile.h"

// for循环里计数用
int i = 0;
int j = 0;
int k = 0;

// 车轮转速 = 编码器脉冲数 * 减速比 / 每圈脉冲数
double calculate_speed(int pluse){
    return pluse * REDUCTION_RATIO / PULSE_PER_CYCLE;
}

double limit_amplitude_absolute(double input, double limit){
	
	if (input > limit) {
		input = limit;
	}else if (input < -limit) {
		input = -limit;
	}
	
	return input;
}

double limit_amplitude_upper_lower(double input, double upper_limit, double lower_limit){
	// 如果上限比下限小, 交换上下限
	if (upper_limit < lower_limit){
		double temp = upper_limit;
		upper_limit = lower_limit;
		lower_limit = temp;		
	}
	
	if (input > upper_limit) {
		input = upper_limit;
	}else if (input < lower_limit) {
		input = lower_limit;
	}

	return input;
}

double average(double *history, int length){
	double sum = 0;
	for (i = 0 ; i < length; i++){
		sum += history[i];
	}
	
	return sum / length ;
}

double median(double *history, int length){
	double temp, median;
	// 冒泡排序
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - 1 - i; j++) {
			if (history[j] > history[j + 1]) {
				temp = history[j];
				history[j] = history[j + 1];
				history[j + 1] = temp;
			}
		}
	}

	// 计算中位数
	if (length % 2 == 0) {
		median = (history[length / 2 - 1] + history[length / 2]) / 2;
	} else {
		median = history[length / 2];
	}

	return median;
}

void move_array_back(double *history, int length){
	for (i = length - 1; i > 0; i--){
		history[i] = history[i - 1];
	}
}

void move_back_and_insert(double *history, int length, double input){
	move_array_back(history, length);
	history[0] = input;
}

double smooth(double *history, int length, double input){
	move_back_and_insert(history, length, input);
	return average(history, length);
}


double diff(double l, double r){
	return (l - r) / (l + r);
}