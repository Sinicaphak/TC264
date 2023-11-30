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
    // Ԫ������
    enum Element_TYPE type;
    // Ԫ�ط���, falseΪ��trueΪ��
    bool dir;
};

enum Element_TYPE {
    // ֱ��
    STRAIGHT = 1,
    // ���
    CURVE = 2,
    // ����
    ROUNDABOUT = 3,
    // ʮ��·��
    CROSS = 4
};
/**
 * ʶ��Ԫ��. 
 * ��������Ӧ����������:
 * element = recognize_element(
 *      leftline, MT9V03X_H / 2, MT9V03X_H - 2, 
 *      rightline, MT9V03X_H / 2, MT9V03X_H - 2
 * );
 * @param leftline_begin ��ʼ��������ߵ�λ��
 * @param leftline_end ������������ߵ�λ��
 * @param rightline_begin ��ʼ�����ұ��ߵ�λ��
 * @param rightline_end ���������ұ��ߵ�λ��
 */
struct Element recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end
);

// endif
#endif