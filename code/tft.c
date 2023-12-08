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
        case (TYPE_ELEMENT) : {
            if (skv->value.vi32 < 0){
                tft180_show_string(x, y, "LL ");
                skv->value.vi32 = -1 * skv->value.vi32;
            } else {
                tft180_show_string(x, y, "R ");
            }
            x += 2 * CHAR_WIDTH;
            switch (skv->value.vi32) {
                case (0) : {
                    tft180_show_string(x, y, "NULL");
                    break;
                };
                case (1) : {
                    tft180_show_string(x, y, "STRAIGHT");
                    break;
                };
                case (2) : {
                    tft180_show_string(x, y, "CURVE");
                    break;
                };
                case (3) : {
                    tft180_show_string(x, y, "ROUNDABOUT");
                    break;
                };
                case (4) : {
                    tft180_show_string(x, y, "CROSS");
                    break;
                };

                default : {
                    tft180_show_string(x, y, "NULL");
                    x += 2 * CHAR_WIDTH;
                    tft180_show_int(x, y, skv->value.vi32, NUM_LENGTH);
                    break;
                }
            }
            break;
        };
    
        default : {
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

    for (i = 0; i < skvs_length; i++){
        tft180_show_string(COLUMN_LEFT_X, i*CHAR_HEIGHT, skvs[i].key);
        show_value(&skvs[i], COLUMN_RIGHT_X, i*CHAR_HEIGHT);
    }
}
