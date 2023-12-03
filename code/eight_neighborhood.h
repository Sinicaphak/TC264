// ifndef
#ifndef _EIGHT_NEIGHBORHOOD_H
#define _EIGHT_NEIGHBORHOOD_H

// Includes
#include "zf_common_headfile.h"

#define THS (20)

enum Direction {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
    DEFAULT = 5,
};

struct Point {
    enum Direction dir;
    int x;
    int y;
};

struct PointNoDir {
    int x;
    int y;
};

extern struct Point sidelines[MT9V03X_H * 2];

struct Point epn(const uint8 image[MT9V03X_H][MT9V03X_W], const int center_x, const int center_y, const enum Direction dir);
void epn_line_left(const uint8 image[MT9V03X_H][MT9V03X_W], struct Point sidelines[MT9V03X_H * 2], enum Direction begin_dir);
void print_sidelines(struct Point sidelines[MT9V03X_H * 2]);

// endif
#endif