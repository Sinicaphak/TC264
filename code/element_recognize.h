// ifndef
#ifndef _ELEMENT_RECOGNIZE_H
#define _ELEMENT_RECOGNIZE_H

#define ROUND_THS_TIME 0
#define ROUND_THS_SINGLE 5

enum ElementType {
    ROUND = 1,
    CROSS = 2,
    NO_ELEMENT = 0
};

struct Point {
    int x;
    int y;
};

extern enum ElementType element_type;

/**
 * 识别元素. 
 * 主函数中应该这样调用:
 * element = recognize_element(
 *      leftline, MT9V03X_H / 2, MT9V03X_H - 2, 
 *      rightline, MT9V03X_H / 2, MT9V03X_H - 2,
 *      int16* trackline
 * );
 * @param leftline_begin 开始处理左边线的位置
 * @param leftline_end 结束处理左边线的位置
 * @param rightline_begin 开始处理右边线的位置
 * @param rightline_end 结束处理右边线的位置
 */
void recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end,
    int16* trackline
);

// endif
#endif