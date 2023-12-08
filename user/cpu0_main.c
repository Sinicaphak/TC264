/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************
#define SKVS_LENGHT 4
#define SKVS_T_LENGHT 3
#define IS_TEST 1

void common_run(void){
   // Ҫ��ӡ����ֵ
    struct ShowKeyValue skvs[SKVS_LENGHT];
    struct ShowKeyValue skv1, skv2, skv3, skv4;

    skv1.key = "version";
    skv1.type = TYPE_UINT;
    skv1.value.vu32 = 66;

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
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // print_binaryzation_image_hl((const double **)mt9v03x_image, MT9V03X_W, MT9V03X_H, 125, RGB565_BLACK, RGB565_WHITE);
            tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);

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
    struct ShowKeyValue skvt1, skvt2, skvt3;

    skvt1.key = "version";
    skvt1.type = TYPE_UINT;
    skvt1.value.vu32 = 15;

    skvt2.key = "ipts0_num";
    skvt2.type = TYPE_INT;
    skvt2.value.vi32 = 114;

    skvt3.key = "ipts1_num";
    skvt3.type = TYPE_INT;
    skvt3.value.vi32 = 514;

    skvs_t[0] = skvt1;


    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // tft180_show_gray_image (0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, 150);
            tft180_displayimage03x((const uint8* )mt9v03x_image, SCREEN_WIDTH, SCREEN_HEIGHT);
            image_process();
            print_sidelines();

            skvt2.value.vi32 = ipts0_num;
            skvt3.value.vi32 = ipts1_num;
            skvs_t[1] = skvt2;
            skvs_t[2] = skvt3;
            show_skvs(&skvs_t, SKVS_T_LENGHT);
            mt9v03x_finish_flag = 0;
        }
    }
}

int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������
    
    init_all();

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    if (IS_TEST){
        test_run();
    } else {
        common_run();
    }

    return 0;
}

#pragma section all restore


// **************************** �������� ****************************
