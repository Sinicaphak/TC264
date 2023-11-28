#include "zf_common_headfile.h"
//zf_device_tft180 tft180_display_font中默认字体为8X16
void show_value(struct ShowKeyValue *skv, uint16 x, uint16 y){
    switch (skv->type) {
        case (TYPE_DOUBLE) : {
            tft180_show_float(x, y, skv->value.d, FLOAT_NUM_LENGTH, FLOAT_POINTNUM_LENGTH);
            break;
        };
        case (TYPE_INT) : {
            tft180_show_int(x, y, skv->value.vi32, NUM_LENGTH);
            break;
        };
        case (TYPE_UINT) : {
            tft180_show_uint(x, y, skv->value.vu32, NUM_LENGTH);
            break;
        };
    
        default: {
            tft180_show_string(x, y, "WRONG_NUM");
            break;
        }
    }
}

void show_skvs(struct ShowKeyValue *skvs, int skvs_length){
    if (skvs_length > SHOW_Y_MAX){
        skvs_length = SHOW_Y_MAX;
    }
    int i = 0;

    /* tft180_show_string(COLUMN_LEFT_X, 0*CHAR_HEIGHT, skvs[0].key);
    show_value(&skvs[0], COLUMN_RIGHT_X, 0*CHAR_HEIGHT);
    tft180_show_string(COLUMN_LEFT_X, 1*CHAR_HEIGHT, skvs[1].key);
    show_value(&skvs[1], COLUMN_RIGHT_X, 1*CHAR_HEIGHT); */

    // 1*CHAR_HEIGHT
    for (i = 0; i < skvs_length; i++){
        /* tft180_show_string(COLUMN_LEFT_X, i*CHAR_HEIGHT, skvs[i].key); */
        show_value(&skvs[i], COLUMN_RIGHT_X, i*CHAR_HEIGHT);
    }
}
