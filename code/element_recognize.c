#include "zf_common_headfile.h"

struct Element element = {
    .type = STRAIGHT,
    .dir = false
}; 

// 将每两个点视为一个向量, 算出两个向量的斜率的差值, 返回最大值
double find_max_slope_diff(int16* sideline, int leftline_begin, int leftline_end) {
    int i = 0;
    double slope1 = 0;
    double slope2 = 0;
    double slope_diff = 0;
    double max_slope_diff = 0;
    for (i = leftline_begin; i < leftline_end - 3; i += 3) {
        slope1 = 2 / (sideline[i + 1] - sideline[i]);
        slope1 = 2 / (sideline[i + 2] - sideline[i + 1]);

        slope_diff = slope1 - slope2;
        if (slope_diff > max_slope_diff) {
            max_slope_diff = slope_diff;
        }
    }
    return max_slope_diff;
}

bool is_in_absolute_limit(double input, double limit) {
    if (input > limit || input < -limit) {
        return false;
    } else {
        return true;
    }
}

struct Element recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end
) {
    double left_slope_diff = 0;
    double right_slope_diff = 0;
    double two_diff = 0;
    struct Element default_element = {
        .type = STRAIGHT,
        .dir = false
    };  
    
    left_slope_diff = find_max_slope_diff(leftline, leftline_begin, leftline_end);
    right_slope_diff = find_max_slope_diff(rightline, rightline_begin, rightline_end);
    two_diff = left_slope_diff - right_slope_diff;
    // 两个斜率差的差值的绝对值小于阈值, 则为直线或弯道, 不用特殊处理
    if (! is_in_absolute_limit(two_diff, TWO_DIFF_THRESHOLD)) {
        // 判断元素位置在左还是右
        if (two_diff > 0) {
            default_element.dir = false;
        } else {
            default_element.dir = true;
        }
        // 判断元素类型
        // 两个值都大于直角时的斜率差值, 则为十字路口
        if (
            ! is_in_absolute_limit(left_slope_diff, RIGHT_ANGLE_SLOPE_DIFF) ||
            ! is_in_absolute_limit(right_slope_diff, RIGHT_ANGLE_SLOPE_DIFF)
        ) {
            default_element.type = CROSS;
        } else {
            // 根据元素位置选择判断哪个斜率差值
            if (default_element.dir) {
                // 右斜率差大于直线时的斜率差值, 则为右环岛
                if (! is_in_absolute_limit(right_slope_diff, CURVE_SLOPE_DIFF) ) {
                    default_element.type = ROUNDABOUT;
                }
            } else {
                // 左斜率差大于直线时的斜率差值, 则为左环岛
                if (! is_in_absolute_limit(left_slope_diff, CURVE_SLOPE_DIFF) ) {
                    default_element.type = ROUNDABOUT;
                }
            } 
        }
    } 
    return default_element;
}

