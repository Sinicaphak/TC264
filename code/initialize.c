#include "zf_common_headfile.h"

// void init_sideline(void){
//     int i = 0;
//     for (i = 0; i < SIDELINES_LENGTH; i++) {
//         sidelines[i].dir = DEFAULT;
//         sidelines[i].x = 0;
//         sidelines[i].y = 0;
//     }
// }


void init_motor(void){
    if (IS_FULL_BRIDGE){
        // 初始化全桥电机
        gpio_init(FULL_BRIDGE_LEFT_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);   
        pwm_init(FULL_BRIDGE_LEFT_PWM, 17000, 0);
        gpio_init(FULL_BRIDGE_RIGHT_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);   
        pwm_init(FULL_BRIDGE_RIGHT_PWM, 17000, 0);
    }else {
        // 初始化半桥电机
        pwm_init(HALF_BRIDGE_LEFT_A, 17000, 0);
        pwm_init(HALF_BRIDGE_LEFT_B, 17000, 0);
        pwm_init(HALF_BRIDGE_RIGHT_A, 17000, 0);
        pwm_init(HALF_BRIDGE_RIGHT_B, 17000, 0);
    }
}

void init_all(void){
    gpio_init(P20_8, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED4 输出 默认高电平 推挽输出模式
    // tft屏幕初始化
    tft180_set_dir(TFT180_CROSSWISE);
    tft180_set_color(RGB565_BLACK, RGB565_WHITE);
    tft180_init();
    mt9v03x_init();
    // 电机初始化
    init_motor();
    // 舵机初始化
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, SERVER_DUTY_MIDDLE);
    // // 编码器初始化
    encoder_dir_init(ENCODER_LEFT, ENCODER_LEFT_A, ENCODER_LEFT_B);                      // 初始化编码器模块与引脚 方向解码编码器模式
    encoder_dir_init(ENCODER_RIGHT, ENCODER_RIGHT_A, ENCODER_RIGHT_B);                      // 初始化编码器模块与引脚 方向解码编码器模式
    pit_ms_init(CCU60_CH1, 2);
    pit_ms_init(CCU60_CH0, 2);

    sm_pid.err_now = 1;
    sm_pid.output = 2;
    ImagePerspective_Init();
    // init_sideline();
}

void test_wireless_pic_init(void) {
    gpio_init(P20_8, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    mt9v03x_init();
    wireless_uart_init();
}