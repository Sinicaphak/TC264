#include "zf_common_headfile.h"


void print_x(int x, int y, rgb565_color_enum color) {
    for (int i = -2; i < 3; i++) {
        if (
            x + i < 1 || x + i > MT9V03X_W - 1 || 
            y + i < 1 || y + i > MT9V03X_H - 1 ||
            y - i < 1 || y - i > MT9V03X_H - 1
        ) {
            continue;
        }
        ips200_draw_point((uint16)(x + i), (uint16)(y + i), color);
        ips200_draw_point((uint16)(x + i), (uint16)(y - i), color);
    }
}

void print_point(struct Point* pois, int pois_len){
    for (int i = 0; i < pois_len; i++) {
        if (i % 2 == 0) {
            print_x(pois[i].x, pois[i].y, RGB565_GREEN);
        } else {
            print_x(pois[i].x, pois[i].y, RGB565_RED);
        }
    }
}
// // {row, col}
// // --------------------> col/x
// // |
// // |
// // \/ row/y
// // 返回突变点
// void recognize_left(
//     int16* leftline, int leftline_begin, int leftline_end, 
//     struct Point* pois, int* pois_len
// ){
//     int i = 0, j = 0,
//         x = 0;
//     double diff_x = 0;
//     for (i = 0; i < MT9V03X_H - 3; i++) {
//         // leftline_begin < y < leftline_end
//         if (i > leftline_end || i < leftline_begin) {
//             continue;
//         }
//         // x < MT9V03X_W / 2
//         if (leftline[i] > MT9V03X_W / 2) {
//             continue;
//         }
//         diff_x = (leftline[i] - leftline[i - 2]);
//         // 算斜率
//         if (  ) {
//             pois[*pois_len].x = x;
//             pois[*pois_len].y = i;
//             (*pois_len)++;
//         }
//     }
// }

// void recognize_right(
//     int16* rightline, int rightline_begin, int rightline_end, 
//     struct Point* pois, int* pois_len
// ){
//     int i = 0, j = 0,
//         x = 0;
//     double diff_x = 0;
// }

void recognize_element (
    int16* leftline, int leftline_begin, int leftline_end, 
    int16* rightline, int rightline_begin, int rightline_end,
    int16* trackline
){
    struct Point* pois_l;
    struct Point* pois_r; 
    int pois_len_l = 0,
        pois_len_r = 0;
    // recognize_left(
    //     leftline, leftline_begin, leftline_end,
    //     pois_l, &pois_len_l
    // );
    // recognize_right(
    //     rightline, rightline_begin, rightline_end,
    //     pois_r, &pois_len_r
    // );
    if (pois_len_l > 0) {
        print_point(pois_l, pois_len_l);
    }
    if (pois_len_r > 0) {
        print_point(pois_r, pois_len_r);
    }
}
