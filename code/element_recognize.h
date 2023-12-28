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
 * ʶ��Ԫ��. 
 * ��������Ӧ����������:
 * element = recognize_element(
 *      leftline, MT9V03X_H / 2, MT9V03X_H - 2, 
 *      rightline, MT9V03X_H / 2, MT9V03X_H - 2,
 *      int16* trackline
 * );
 * @param leftline_begin ��ʼ��������ߵ�λ��
 * @param leftline_end ������������ߵ�λ��
 * @param rightline_begin ��ʼ�����ұ��ߵ�λ��
 * @param rightline_end ���������ұ��ߵ�λ��
 */
void recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end,
    int16* trackline
);

// endif
#endif