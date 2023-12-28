// // ifndef
// #ifndef _CONVOLUTION_H
// #define _CONVOLUTION_H

// #define THRESHOLD (150)

// // include 
// #include "zf_common_headfile.h"

// struct ConvolutionCore {
//     int side_length;
//     int half_side_length;
//     double** core;
// };

// extern struct ConvolutionCore cc;
// // 二值化结果放在result里
// void binaryzation(const uint8** image, uint16 x, uint16 y, uint8** result);
// void convolution(const uint8** image, uint16 image_x, uint16 image_y, struct ConvolutionCore* core, double** result);
// void print_binaryzation_image(
//     const double** image, uint16 image_x, uint16 image_y,
//     double threshold, rgb565_color_enum high_color
// );
// void print_binaryzation_image_hl(
//     const double** image, uint16 image_x, uint16 image_y,
//     double threshold, rgb565_color_enum high_color, rgb565_color_enum low_color
// );

// // endif
// #endif