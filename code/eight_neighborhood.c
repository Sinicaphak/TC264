// #include "zf_common_headfile.h"

// struct Point sidelines[SIDELINES_LENGTH];
// #define MAX_SHIFT_COUNT 5
// int ex_count = 514;

// // {row, col}
// // ----------> col/x
// // |
// // |
// // |
// // \/ row/y
// // ����Ϊ��һ������, ��תӦ��ʹ��������ô�ƶ�
// const int dir_left[4][2] = {
//     {-1, -1},
//     {-1, 1},
//     {1, 1},
//     {1, -1},
// };
// // ����Ϊ��һ������, ǰ��Ӧ��ʹ��������ô�ƶ�
// const int dir_front[4][2] = {
//     {0, -1},
//     {-1, 0},
//     {0, 1},
//     {1, 0},
// };
// // ����Ϊ��һ������, ��תӦ��ʹ��������ô�ƶ�
// const int dir_right[4][2] = {
//     {1, 1},
//     {1, -1},
//     {-1, -1},
//     {-1, 1},
// };


// double diff_ratio_sum(double a, double b){
//     double output = 0;
//     double diff = 0;
//     double sum = 0;

//     diff = (int)(a - b) << 8;
//     sum = a + b;
//     output =  diff / sum;
//     if (output < 0) {
//        output = -output;
//     }

//     return output;
// }

// struct Point find_front_point(int now_x, int now_y, enum Direction dir){
//     struct Point point = {
//         .dir = dir,
//         .x = now_x + dir_front[dir][0],
//         .y = now_y + dir_front[dir][1],
//     };

//     return point;
// }

// struct Point find_front_left_point(int now_x, int now_y, enum Direction dir){
//     struct Point point = {
//         .dir = dir,
//         .x = now_x + dir_left[dir][0],
//         .y = now_y + dir_left[dir][1],
//     };

//     return point;
// }


// void epn_line_left(
//     struct Point sidelines[], 
//     struct Point begin_point,
//     int count_now
// ){
//     struct Point f_point, fl_point, record_point;
//     double drs_fl, drs_f;
//     int count = count_now, turn = 0;
//     enum Direction dir = begin_point.dir;
//     int x = begin_point.x, y = begin_point.y;
//     while ( 
//         2 < x &&
//         x < (X_MAX / 2) - 1 && 
//         2 < y && 
//         y < Y_MAX - 1 && 
//         turn <= 4 &&
//         count < SIDELINES_LENGTH
//     ) {
//         // �����ĵ��ǰ�������ص���в�Ⱥ�
//         f_point = find_front_point(x, y, dir);
//         drs_f = diff_ratio_sum(mt9v03x_image[f_point.x][f_point.y], mt9v03x_image[x][y]);
//         // �����ĵ����ǰ�������ص���в�Ⱥ�
//         fl_point = find_front_left_point(x, y, dir);
//         drs_fl = diff_ratio_sum(mt9v03x_image[fl_point.x][fl_point.y], mt9v03x_image[x][y]);

//         record_point = sidelines[count];
//         if (drs_f > THS) {
//             // ��ת
//             dir = (dir + 3) % 4;
//             turn = 0;
//         } else if (drs_fl > THS) {
//             // ǰ��
//             x += dir_front[dir][0];
//             y += dir_front[dir][1];
//             sidelines[count].x = x;
//             sidelines[count].y = y;
//             sidelines[count].dir = dir;
//             count++;
//             turn = 0;
//         } else {
//             // ��ת
//             x += dir_left[dir][0];
//             y += dir_left[dir][1];
//             dir = (dir + 1) % 4;
//             sidelines[count].x = x;
//             sidelines[count].y = y;
//             sidelines[count].dir = dir;
//             turn++;
//             count++;
//         }
//     }
// /*     ex_count = count; */
// }

// void track_line(    
//     struct Point sidelines[]
// ){
//     struct Point f_point, fl_point, input_point;
//     double drs_fl, drs_f;
//     int count = 0, shift_count = 0;
//     enum Direction dir = LEFT;
//     int x = X_MAX / 2, y = Y_MAX - 2;

//     init_sideline();

//     while (
//         x > 1
//     ) {
//         // �����ĵ��ǰ�������ص���в�Ⱥ�
//         f_point = find_front_point(x, y, dir);
//         drs_f = diff_ratio_sum(mt9v03x_image[f_point.x][f_point.y], mt9v03x_image[x][y]);
//         // �����ĵ����ǰ�������ص���в�Ⱥ�
//         fl_point = find_front_left_point(x, y, dir);
//         drs_fl = diff_ratio_sum(mt9v03x_image[fl_point.x][fl_point.y], mt9v03x_image[x][y]);

//         // �����ǰ����ǰ�������ص�����ĵ�����ص��Ⱥʹ�����ֵ, ��ΪѰ������, ��ת��ʼѲ��
//         if (drs_fl > THS || drs_f > THS) {
//             shift_count++;
//             if (shift_count > MAX_SHIFT_COUNT) {
//                 dir = (dir + 3) % 4;
//                 break;
//             }
//         }
//         x += dir_front[dir][0];  
//         // sidelines[count].x = x;
//         // sidelines[count].y = y;
//         // sidelines[count].dir = dir;
//         // count++;
//     }
    
//     ex_count = count;
    
//     if (x > 1) {
//         input_point.x = x;
//         input_point.y = y;
//         input_point.dir = dir;
//         epn_line_left(sidelines, input_point, 0);
//     }

// }

// void print_sidelines(struct Point sidelines[]){
//     int i = 0, k;
//     struct Point point_now;
//     for(i = 0; i < SIDELINES_LENGTH; i++){
//         point_now = sidelines[i];
//         if (point_now.dir == DEFAULT) {
//             break;
//         }
//         ips200_draw_point((uint16)(point_now.x), (uint16)(point_now.y), RGB565_RED);
//         // for (k = -1; k < 2; k++) {
//         //     ips200_draw_point((uint16)(point_now.x), (uint16)(point_now.y + k), RGB565_RED);
//         //     ips200_draw_point((uint16)(point_now.x), (uint16)(point_now.y + k), RGB565_RED);   
//         //     ips200_draw_point((uint16)(point_now.x), (uint16)(point_now.y + k), RGB565_RED);
//         // }
//         // ips200_draw_point((uint16)(i), (uint16)(128 / 2), RGB565_GREEN);
//     }
// }


