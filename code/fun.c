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
 * @brief 将右边线修正为屏幕中间的线
 * 右边线方程: x = fk * y + b + MT9V03X_W/2
 */
int correct_right_border(int x, int y){
	return x - (y * RIGHTLINE_KF + RIGHTLINE_B);
}
/**
 * @brief 将左边线修正为屏幕中间的线
 * 左边线方程: x = fk * y + b
 */
int correct_left_border(int x, int y){
	return x + (y * LEFTLINE_KF + LEFTLINE_B);
}
/**
 * @brief 补线: 从屏幕上面向屏幕下面补
 * @param begin_y: 开始补线的y坐标
 * @param end_y: 结束补线的y坐标
 * @param begin_x: 开始补线的x坐标
 * @param end_x: 结束补线的x坐标
 * @param line_need_fix: 需要补线的边线
 * @param is_left: 左边线补线为1, 右边线补线为0
 */
void fix_line(int begin_y, int end_y, int end_x, int begin_x, int line_need_fix[MT9V03X_H], bool is_left) {
    int i = 0;
    double kf = 0; 	// 反斜率
    if (begin_y > end_y) {
        i = end_y;
        end_y = begin_y;
        begin_y = i;
    }
    // kf = ((double)(line_need_fix[end_y] - line_need_fix[begin_y]) / (double)(end_y - begin_y));
    kf = ((double)(end_x - begin_x) / (double)(end_y - begin_y));

    for (i = begin_y + 1; i < end_y; i++) {
        // line_need_fix[i] = clap(line_need_fix[begin_y] + (i - begin_y) * kf, MT9V03X_W - 1, 1);
        line_need_fix[i] = clap(begin_x + (i - begin_y) * kf, MT9V03X_W - 1, 1);
    }
}

void self_log(const char *str){
	tft180_clear();
	zf_log(0, str);
}

int clap(int input, int up, int down) {
	if (up < down) {
		int temp = up;
		up = down;
		down = temp;
	}

	if (input > up) {
		return up;
	}
	if (input < down) {
		return down;
	}
	return input;
}