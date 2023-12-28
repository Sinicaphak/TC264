// #include "zf_common_headfile.h"

// double core_array[3][3] = {
//     {-1, 0, 1},
//     {-1, 0, 1},
//     {-1, 0, 1}
// };
// struct ConvolutionCore cc = {
//     .side_length = 3,
//     .half_side_length = 1,
//     .core = core_array
// };
// uint8 black_white_image[MT9V03X_H][MT9V03X_W]; 


// double convolution_point(const uint8** image, uint16 now_x, uint16 now_y, struct ConvolutionCore* core) {
//     int i, j;
//     double sum = 0;
//     for (i = 0; i < core->side_length; i++) {
//         for (j = 0; j < core->side_length; j++) {
//             sum += (image[now_x - core->half_side_length + i ][now_y - core->half_side_length + j]) * (core->core[i][j]);
//         }
//     }
//     return sum;
// }

// void convolution(const uint8** image, uint16 image_x, uint16 image_y, struct ConvolutionCore* core, double** result) {
//     uint16 i, j;
//     double end_result[image_y][image_x];
//     for (i = 0; i < image_x; i++) {
//         for (j = 0; j < image_y; j++) {
//             if ( 
//                 (i < core->half_side_length) || 
//                 (j < core->half_side_length) ||
//                 (i > image_x - core->half_side_length - 1) ||
//                 (j > image_y - core->half_side_length - 1)
//             ) {
//                 end_result[j][i] = 0x0000;
//             } else {
//                 end_result[j][i] = convolution_point(image, j, i, core);
//             }
//         }
//     }
//     result = end_result;
// }

// // ¶þÖµ»¯
// void binaryzation(const uint8** image, uint16 x, uint16 y, uint8** result) {
//     int i, j;
//     uint8 end_result[y][x];
//     for (i = 0; i < y; i++) {
//         for (j = 0; j < x; j++) {
//             if (image[i][j] > THRESHOLD) {
//                 end_result[i][j] = 0x0000;
//             } else {
//                 end_result[i][j] = 0xFFFF;
//             }
//         }
//     }
//     result = end_result;
// }

// void print_binaryzation_image_hl(
//     const double** image, uint16 image_x, uint16 image_y,
//     double threshold, rgb565_color_enum high_color, rgb565_color_enum low_color
// ) {
//     uint16 i, j;
//     for (i = 0; i < image_x; i++) {
//         for (j = 0; j < image_y; j++) {
//             if (image[j][i] > threshold) {
//                 ips200_draw_point(i, j, high_color);
//             }else {
//                 ips200_draw_point(i, j, low_color);
//             }
//         }
//     }
// }

// void print_binaryzation_image(
//     const double** image, uint16 image_x, uint16 image_y,
//     double threshold, rgb565_color_enum high_color
// ) {
//     uint16 i, j;
//     for (i = 0; i < image_x; i++) {
//         for (j = 0; j < image_y; j++) {
//             if (image[j][i] > threshold) {
//                 ips200_draw_point(i, j, high_color);
//             }
//         }
//     }
// }
