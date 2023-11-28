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
#define skvs_lenght 4
#define skvs_a_lenght 2


int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������
    
    init_all();
    // Ҫ��ӡ����ֵ
    struct ShowKeyValue skvs[skvs_lenght], skvs_a[skvs_a_lenght];
    struct ShowKeyValue skv1, skv2, skv3, skv4;
    struct ShowKeyValue skva1, skva2;

    skv1.key = "version";
    skv1.type = TYPE_DOUBLE;
    skv1.value.d = 64;

    skv2.key = "smpid.in";
    skv2.type = TYPE_DOUBLE;
    skv2.value.d = 114;

    skv3.key = "smpid.out";
    skv3.type = TYPE_DOUBLE;
    skv3.value.d = 514;

    skv4.key = "servo_out";
    skv4.type = TYPE_DOUBLE;
    skv4.value.d = 1919;
    
    skva1.key = "l";
    skva1.type = TYPE_INT;
    skva1.value.d = 1919;
    
    skva2.key = "r";
    skva2.type = TYPE_INT;
    skva2.value.d = 810;

    skvs[0] = skv1;

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
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
        show_skvs(skvs, skvs_lenght);
        //ѭ��ִ�еĴ���
        // skva1.value.vi32 = encoder_data_l;
        // skva2.value.vi32 = encoder_data_r;
        // printf("%d, %d, %f\n", encoder_data_l, encoder_data_r, target_speed);
        // show_skvs(skvs_a, skvs_a_lenght);
    }
}

#pragma section all restore


// **************************** �������� ****************************
