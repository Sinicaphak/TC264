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
#define SKVS_LENGHT 1
#define SKVS_T_LENGHT 2
#define IS_TEST 1

void common_run(void){
    // Ҫ��ӡ����ֵ
    struct ShowKeyValue skvs[SKVS_LENGHT];
    struct ShowKeyValue skv1, skv2, skv3, skv4;

    skv1.key = "version";
    skv1.type = TYPE_UINT;
    skv1.value.vu32 = 14;

    skv2.key = "rs";
    skv2.type = TYPE_ROUND_STATE;

    skvs[0] = skv1;
    skvs[1] = skv2;
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // print_binaryzation_image_hl((const double **)mt9v03x_image, MT9V03X_W, MT9V03X_H, 125, RGB565_BLACK, RGB565_WHITE);
            tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);

            image_boundary_process();
            switch_trackline();
            process_data();
            show_line();

            // printf("%d, %d, %f, %f\n", encoder_data_l, encoder_data_r, motor_input_l, motor_input_r);
            show_skvs(skvs, SKVS_LENGHT); 

            mt9v03x_finish_flag = 0;
        }
        
    }
}
void test_run(void){
    struct ShowKeyValue skvs_t[SKVS_T_LENGHT];
    struct ShowKeyValue skvt1, skvt2;

    skvt1.key = "v_t";
    skvt1.type = TYPE_UINT;
    skvt1.value.vu32 = 22;

    skvt2.key = "rs";
    skvt2.type = TYPE_ROUND_STATE;

    skvs_t[0] = skvt1;
    skvs_t[1] = skvt2;

    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // tft180_show_gray_image (0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, 150);
            tft180_displayimage03x((const uint8* )mt9v03x_image, SCREEN_WIDTH, SCREEN_HEIGHT);
            image_boundary_process();
            switch_trackline();
            process_data();
            show_line();
            show_mark();

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
