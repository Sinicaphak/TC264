#include "zf_common_headfile.h"
//zf_device_tft180 tft180_display_font中默认字体为8X16
void show_value(struct ShowKeyValue *skv, uint16 y){
    switch (skv->type) {
        case (TYPE_DOUBLE) : {
            tft180_show_float(COLUMN_RIGHT_X, y, skv->value->d, FLOAT_NUM_LENGTH, FLOAT_POINTNUM_LENGTH);
            break;
        };
        case (TYPE_INT) : {
            tft180_show_int(COLUMN_RIGHT_X, y, skv->value->vi32, NUM_LENGTH);
            break;
        };
        case (TYPE_UINT) : {
            tft180_show_int(COLUMN_RIGHT_X, y, skv->value->vu32, NUM_LENGTH);
            break;
        };
    
        default: {
            tft180_show_string(COLUMN_RIGHT_X,  y,   "WRONG_NUM");
            break;
        }
    }
}

void show_skvs(struct ShowKeyValue *skvs, int skvs_length){
    if (skvs_length > SHOW_Y_MAX){
        skvs_length = SHOW_Y_MAX;
    }
    int i = 0;
    for (i = 0; i < skvs_length; i++){
        tft180_show_string(COLUMN_LEFT_X, CHAR_HEIGHT*i, skvs[i].key);
        show_value(&skvs[i], CHAR_HEIGHT*i);
        i++;
    }
}