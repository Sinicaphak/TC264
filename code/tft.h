// ifdef
#ifndef _TFT_H_
#define _TFT_H_
//zf_device_tft180 tft180_display_font��Ĭ��������Ϊ8X16
#define CHAR_WIDTH (8)
#define CHAR_HEIGHT (16)
// ��һ�е���ʼx����
#define COLUMN_LEFT_X (0*CHAR_WIDTH)
// �ڶ��е���ʼx����
#define COLUMN_RIGHT_X (10*CHAR_WIDTH)
// ��ʾ�������ĳ���
#define FLOAT_NUM_LENGTH (5)
#define FLOAT_POINTNUM_LENGTH (2)
#define NUM_LENGTH (5)

#define SHOW_Y_MAX (7)

// ShowKeyValue�п��ܳ��ֵ�����
enum ShowValueType {
    TYPE_DOUBLE,
    TYPE_UINT,
    TYPE_INT,
};
// ShowKeyValue�п��ܳ��ֵ�ֵ
union ShowValue {
    double d;
    int32 vi32;
    uint32 vu32;
};
// keyΪ�ַ���, typeΪֵ������, valueΪֵ
struct ShowKeyValue {
    const char *key;
    enum ShowValueType type;
    union ShowValue *value;
};

void show_skvs(struct ShowKeyValue *skvs, int skvs_length);

// endif
#endif



