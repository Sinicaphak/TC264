#include "zf_common_headfile.h"

double safe_count = 0;

struct Point sidelines[MT9V03X_H * 2] = {
    {0, 0, DEFAULT}
}; 

double diff_ratio_sum(double a, double b){
    double output = 0;
    double diff = 0;
    double sum = 0;

    diff = (int)(a - b) << 8;
    sum = a + b;
    output =  diff / sum;
    if (output < 0) {
       output = -output;
    }

    return output;
}

struct Point epn(const uint8 image[MT9V03X_H][MT9V03X_W], const int center_x, const int center_y, const enum Direction dir) {
    struct Point point = {
        .dir = dir,
        .x = center_x,
        .y = center_y,
    };

    double drs_lf = 0;
    double drs_f = 0;
    int flag = 0;
    // 前方元素
    uint8 front;
    // 左前方元素
    uint8 left_front;

    switch(dir) {
        case UP:
            front = image[center_x - 1][center_y];
            left_front = image[center_x - 1][center_y - 1];
            break;
        case DOWN:
            front = image[center_x + 1][center_y];
            left_front = image[center_x + 1][center_y + 1];
            break;
        case LEFT:
            front = image[center_x][center_y - 1];
            left_front = image[center_x + 1][center_y - 1];
            break;
        case RIGHT:
            front = image[center_x][center_y + 1];
            left_front = image[center_x - 1][center_y + 1];
            break;
    }

    drs_lf = diff_ratio_sum(left_front, image[center_x][center_y]);
    drs_f = diff_ratio_sum(front, image[center_x][center_y]);
    if (drs_f > THS) {
        if (drs_lf > THS) {
            flag = 1;
        } else {
            flag = 2;
        }
    } else {
        if (drs_lf > THS) {
            flag = 3;
        } else {
            flag = 4;
        }
    }

    switch (flag) {
        case (4): {
            // 前方与左前方都没有障碍物
            point.x = center_x - 1;
            point.y = center_y - 1;
            point.dir = ((dir + 1) % 4);
            break;
        };
        // 前方有障碍物
        case (1): {
            // 前方有障碍物, 左前没方有障碍物
            point.dir = ((dir + 1) % 4);
            break;
        };
        case (2): {
            // 前方与左前方都有障碍物
            point.dir = ((dir + 1) % 4);
            break;
        };
        case (3): {
            // 前方没有障碍物, 左前方有障碍物
            // 保持原方向
            point.x = center_x - 1;
            break;
        };
    
        default: {
            break;
        }
    }

    return point;
}

void epn_line_left(const uint8 image[MT9V03X_H][MT9V03X_W], struct Point sidelines[MT9V03X_H * 2], enum Direction begin_dir){
    int i, j, count = 0;
    struct Point point;
    int before_x = MT9V03X_W / 2;
    int before_y = 1;
    int x = MT9V03X_W / 2;
    int y = 1;
    enum Direction dir = begin_dir;
    struct Point point_count;

    // 从初始方向开始寻, 直到找到前方和侧前方都有障碍才开始转向
    while (dir == begin_dir && x > 1) {
        point = epn(image, x, y, dir);
        if (point.dir == DOWN) {
            dir = begin_dir;
        }
        safe_count++;
        if ( safe_count > ((MT9V03X_H / 2) + 3) ){
            break;
        }
        point_count = sidelines[count];
        point_count.x = point.x;
        point_count.y = point.y;
        point_count.dir = point.dir;
        x--;
    }
    safe_count = 0;

    while ( y < MT9V03X_H ) {
        point = epn(image, x, y, dir);
        dir = point.dir;
        x = point.x;
        y = point.y;

        if (! (x == before_x && y == before_y)) {
            point_count = sidelines[count];
            point_count.x = point.x;
            point_count.y = point.y;
            point_count.dir = point.dir;
            count++;
        }
        before_x = x;
        before_y = y;

        if (count > MT9V03X_H * 2) {
            break;
        }
    }
    
}

void print_sidelines(struct Point sidelines[MT9V03X_H * 2]){
    int i = 0;
    struct Point point_now;
    for(i = 0; i < MT9V03X_H * 2; i++){
        point_now = sidelines[i];
        if (point_now.dir == DEFAULT) {
            break;
        }
        ips200_draw_point((uint16)(point_now.x), (uint16)(point_now.y), RGB565_BLUE);
    }
}


