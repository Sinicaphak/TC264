// ifndef
#ifndef _ELEMENT_RECOGNIZE_H
#define _ELEMENT_RECOGNIZE_H

#define RIGHT_ANGLE_SLOPE_DIFF 100
#define CURVE_SLOPE_DIFF 1
#define TWO_DIFF_THRESHOLD 1e-1

// include
#include "zf_common_headfile.h"
extern struct Element element;

struct Element {
    // 元素类型
    enum Element_TYPE type;
    // 元素方向, false为左，true为右
    bool dir;
};

enum Element_TYPE {
    // 直线
    STRAIGHT = 1,
    // 弯道
    CURVE = 2,
    // 环岛
    ROUNDABOUT = 3,
    // 十字路口
    CROSS = 4
};
/**
 * 识别元素. 
 * 主函数中应该这样调用:
 * element = recognize_element(
 *      leftline, MT9V03X_H / 2, MT9V03X_H - 2, 
 *      rightline, MT9V03X_H / 2, MT9V03X_H - 2
 * );
 * @param leftline_begin 开始处理左边线的位置
 * @param leftline_end 结束处理左边线的位置
 * @param rightline_begin 开始处理右边线的位置
 * @param rightline_end 结束处理右边线的位置
 */
struct Element recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end
);

// endif
#endif