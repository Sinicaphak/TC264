#include "zf_common_headfile.h"

//zf_device_tft180 tft180_display_font中默认字体为8X16
void show_value(struct ShowKeyValue *skv, int x, int y){
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
        case (TYPE_ELEMENT_STATE) : {
            struct ShowKeyValue skv_inner;
            skv_inner.key = skv->key;  
            switch (element_type) {
                case (NO_ELEMENT) : {
                    tft180_show_string(x, y, "NULL");
                    break;
                };
                case (CROSS) : {
                    skv_inner.type = TYPE_CROSS_STATE;
                    show_value(&skv_inner, x, y);
                    break;
                };
                case (ROUND) : {
                    skv_inner.type = TYPE_ROUND_STATE;
                    show_value(&skv_inner, x, y);
                    break;
                };
                default: {
                    break;
                }
            }
            break;
        };
        case (TYPE_ROUND_STATE) : {
            switch (round_state) {
                case (NO_ROUND) : {
                    tft180_show_string(x, y, "N_R");
                    break;
                };
                case (PRE_IN_ROUND) : {
                    tft180_show_string(x, y, "P_IR");
                    break;
                };
                case (READY_IN_ROUND) : {
                    tft180_show_string(x, y, "R_IR");
                    break;
                };
                case (IN_ROUND) : {
                    tft180_show_string(x, y, "IR");
                    break;
                };
                case (ROUNDING) : {
                    tft180_show_string(x, y, "RING");
                    break;
                };
                case (READY_OUT_ROUND) : {
                    tft180_show_string(x, y, "R_OR");
                    break;
                };
                case (OUT_ROUND) : {
                    tft180_show_string(x, y, "OR");
                    break;
                };
                case (ROUND_END) : {
                    tft180_show_string(x, y, "R_E");
                    break;
                };
                case (MID_ROUND) : {
                    tft180_show_string(x, y, "M_R");
                    break;
                };
                case (BEFORE_ROUND) : {
                    tft180_show_string(x, y, "B_R");
                    break;
                };
                default : {
                    tft180_show_string(x, y, "WRS");
                    break;
                }
            }
            break;
        }
        case (TYPE_CROSS_STATE) : {
            switch (cross_state) {
                case (NO_CROSS) : {
                    tft180_show_string(x, y, "N_C");
                    break;
                };
                case (SPOT_CROSS) : {
                    tft180_show_string(x, y, "S_C");
                    break;
                };
                case (IN_CROSS) : {
                    tft180_show_string(x, y, "I_C");
                    break;
                };
                default : {
                    tft180_show_string(x, y, "W_CS");
                    break;
                }
            }
        }
        case (TYPE_BOOLEAN) : {
            if (skv->value.bo){
                tft180_show_string(x, y, "T");
            } else {
                tft180_show_string(x, y, "F");
            }
            break;
        }
        case (TYPE_TRACKLINE) : {
            switch (track_type) {
                case TRACK_LEFT : {
                    tft180_show_string(x, y, "L");
                    break;
                }
                case TRACK_MID : {
                    tft180_show_string(x, y, "M");
                    break;
                }
                case TRACK_RIGHT : {
                    tft180_show_string(x, y, "R");
                    break;
                }
                
                default: {
                    tft180_show_string(x, y, "W_RT");
                    break;
                }
            }
            break;
        }
        case (TYPE_DIR) : {
            switch (round_dir) {
                case NO_DIR : {
                    tft180_show_string(x, y, "N_D");
                    break;
                };
                case LEFT_DIR : {
                    tft180_show_string(x, y, "L_D");
                    break;
                };
                case RIGHT_DIR : {
                    tft180_show_string(x, y, "R_D");
                    break;
                };
                default:
                    tft180_show_string(x, y, "W_D");
                    break;
                }
            break;
        }
        
        default : {
            tft180_show_string(x, y, "W_N");
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
        // tft180_show_string(COLUMN_LEFT_X, i*CHAR_HEIGHT, skvs[i].key);
        show_value(&skvs[i], COLUMN_RIGHT_X, i*CHAR_HEIGHT);
        // show_value(&skvs[i], COLUMN_LEFT_X, i*CHAR_HEIGHT);
    }
}