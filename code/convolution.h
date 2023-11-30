// ifndef
#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H

#define THRESHOLD (150)

// include 
#include "zf_common_headfile.h"

struct ConvolutionCore {
    int side_length;
    int half_side_length;
    double** core;
};

void binaryzation(uint8* image, uint16 x, uint16 y);
void convolution(const uint8* image, uint16 image_x, uint16 image_y, struct ConvolutionCore* core, double** result);
void print_convoluted_image(double** image, uint16 image_x, uint16 image_y, double threshold, rgb565_color_enum high_color);
void print_binaryzation_image_hl(
    double** image, uint16 image_x, uint16 image_y,
    double threshold, rgb565_color_enum high_color, rgb565_color_enum low_color
);

// endif
#endif