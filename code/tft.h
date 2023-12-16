// ifdef
#ifndef _TFT_H_
#define _TFT_H_
//zf_device_tft180 tft180_display_font中默认字体宽高为8X16
#define CHAR_WIDTH (8)
#define CHAR_HEIGHT (16)
// 第一列的起始x坐标
#define COLUMN_LEFT_X (0*CHAR_WIDTH)
// 第二列的起始x坐标
#define COLUMN_RIGHT_X (5*CHAR_WIDTH)
// 显示浮点数的长度
#define FLOAT_NUM_LENGTH (5)
#define FLOAT_POINTNUM_LENGTH (2)
#define NUM_LENGTH (3)

#define SHOW_Y_MAX (10)

// ShowKeyValue中可能出现的类型
enum ShowValueType {
    TYPE_DOUBLE,
    TYPE_UINT,
    TYPE_INT,
    TYPE_ELEMENT,
    TYPE_ROUND_STATE,
    TYPE_BOOLEAN,
    TYPE_TRACKLINE,
    TYPE_DIR
};
// ShowKeyValue中可能出现的值
union ShowValue {
    double d;
    int vi32;
    uint32 vu32;
    boolean bo;
};
// key为字符串, type为值的类型, value为值
struct ShowKeyValue {
    const char *key;
    enum ShowValueType type;
    union ShowValue value;
};

void show_skvs(struct ShowKeyValue *skvs, int skvs_length);

// endif
#endif



