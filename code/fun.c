#include "zf_common_headfile.h"


// forѭ���������
int i = 0;
int j = 0;
int k = 0;

// ����ת�� = ������������ * ���ٱ� / ÿȦ������
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
	// ������ޱ�����С, ����������
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
	// ð������
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - 1 - i; j++) {
			if (history[j] > history[j + 1]) {
				temp = history[j];
				history[j] = history[j + 1];
				history[j + 1] = temp;
			}
		}
	}

	// ������λ��
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

double sliding_window_filter(double *history, int length, double input, double threshold){
	double output = 0;
	double average_value = 0;	
	average_value = smooth(history, length, input);
	
	if (fabs(input - average_value) > threshold){
		output = average_value;
	}else{
		output = input;
	}
	
	return output;

}

void draw_matrix(void) {
    uint16 start_x = (SCREEN_WIDTH - MATRIX_SIZE) / 2;
    uint16 start_y = (SCREEN_HEIGHT - MATRIX_SIZE) / 2;
    uint16 x, y;

    for ( y = start_y; y < start_y + MATRIX_SIZE; y++) {
        for ( x = start_x; x < start_x + MATRIX_SIZE; x++) {
            ips200_draw_point(x, y, RGB565_RED);
        }
    }
}
/**
 * @brief ���ұ�������Ϊ��Ļ�м����
 * �ұ��߷���: x = fk * y + b + MT9V03X_W/2
 */
int correct_right_border(int x, int y){
	return x - (y * RIGHTLINE_KF + RIGHTLINE_B);
}