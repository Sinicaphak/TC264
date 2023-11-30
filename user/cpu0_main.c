/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
#define SKVS_LENGHT 4
#define SKVS_T_LENGHT 2

void common_run(void){
   // 要打印的数值
    struct ShowKeyValue skvs[SKVS_LENGHT];
    struct ShowKeyValue skv1, skv2, skv3, skv4;

    skv1.key = "version";
    skv1.type = TYPE_UINT;
    skv1.value.vu32 = 65;

    skv2.key = "smpid.in";
    skv2.type = TYPE_DOUBLE;
    skv2.value.d = 114;

    skv3.key = "smpid.out";
    skv3.type = TYPE_DOUBLE;
    skv3.value.d = 514;

    skv4.key = "servo_out";
    skv4.type = TYPE_DOUBLE;
    skv4.value.d = 1919;

    skvs[0] = skv1;


    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        if(mt9v03x_finish_flag) {
            print_binaryzation_image_hl((double **)mt9v03x_image, MT9V03X_W, MT9V03X_H, 125, RGB565_BLACK, RGB565_WHITE);
            // tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);
            image_boundary_process();
            switch_trackline();
            show_line();
            process_data();

            skv2.key = "smpid.in";
            skv2.type = TYPE_DOUBLE;
            skv2.value.d = sm_pid.err_now;

            skv3.key = "smpid.out";
            skv3.type = TYPE_DOUBLE;
            skv3.value.d = sm_pid.output;

            skv4.key = "servo_out";
            skv4.type = TYPE_DOUBLE;
            skv4.value.d = server_motor_input;
            skvs[1] = skv2;
            skvs[2] = skv3;
            skvs[3] = skv4;

            mt9v03x_finish_flag = 0;
        }
        show_skvs(skvs, SKVS_LENGHT);
    }
}

void test_run(void){
    struct ShowKeyValue skvs_t[SKVS_T_LENGHT];
    struct ShowKeyValue skvt1, skvt2;
    double result[MT9V03X_H][MT9V03X_W];

    skvt1.key = "version";
    skvt1.type = TYPE_UINT;
    skvt1.value.vu32 = 965;

    skvt2.key = "element";
    skvt2.type = TYPE_ELEMENT;
    skvt2.value.vi32 = 0;

    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        if(mt9v03x_finish_flag) {
            tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);
            convolution((uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, &cc, result);
            print_binaryzation_image(result, MT9V03X_W, MT9V03X_H, 150, RGB565_GREEN);
            // if (element.dir){
            //     skvt2.value.vi32 = element.type;
            // } else {
            //     skvt2.value.vi32 = -1 * element.type;
            // };
            mt9v03x_finish_flag = 0;
        }
        // skvs_t[0] = skvt1;
        // skvs_t[1] = skvt2;
        // show_skvs(skvs_t, SKVS_LENGHT);
    }
}

int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    
    init_all();

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    // common_run();
    test_run();
}

#pragma section all restore


// **************************** 代码区域 ****************************
