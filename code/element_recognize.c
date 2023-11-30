#include "zf_common_headfile.h"

struct Element element = {
    .type = STRAIGHT,
    .dir = false
}; 

// ��ÿ��������Ϊһ������, �������������б�ʵĲ�ֵ, �������ֵ
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
    // ����б�ʲ�Ĳ�ֵ�ľ���ֵС����ֵ, ��Ϊֱ�߻����, �������⴦��
    if (! is_in_absolute_limit(two_diff, TWO_DIFF_THRESHOLD)) {
        // �ж�Ԫ��λ����������
        if (two_diff > 0) {
            default_element.dir = false;
        } else {
            default_element.dir = true;
        }
        // �ж�Ԫ������
        // ����ֵ������ֱ��ʱ��б�ʲ�ֵ, ��Ϊʮ��·��
        if (
            ! is_in_absolute_limit(left_slope_diff, RIGHT_ANGLE_SLOPE_DIFF) ||
            ! is_in_absolute_limit(right_slope_diff, RIGHT_ANGLE_SLOPE_DIFF)
        ) {
            default_element.type = CROSS;
        } else {
            // ����Ԫ��λ��ѡ���ж��ĸ�б�ʲ�ֵ
            if (default_element.dir) {
                // ��б�ʲ����ֱ��ʱ��б�ʲ�ֵ, ��Ϊ�һ���
                if (! is_in_absolute_limit(right_slope_diff, CURVE_SLOPE_DIFF) ) {
                    default_element.type = ROUNDABOUT;
                }
            } else {
                // ��б�ʲ����ֱ��ʱ��б�ʲ�ֵ, ��Ϊ�󻷵�
                if (! is_in_absolute_limit(left_slope_diff, CURVE_SLOPE_DIFF) ) {
                    default_element.type = ROUNDABOUT;
                }
            } 
        }
    } 
    return default_element;
}

