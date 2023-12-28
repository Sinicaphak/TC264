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
#define SKVS_T_LENGHT 6
#define SKVS_T1_LENGHT 4
#define IS_TEST 1

uint8 send_buff = 0;

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
    struct ShowKeyValue skvt1, skvt2, skvt3, skvt4, skvt5, skvt6, skvt7, skvt8, skvt9;

    skvt1.key = "v_t";
    skvt1.type = TYPE_UINT;
    skvt1.value.vu32 = 6;
    skvs_t[0] = skvt1;
    
    skvt2.key = "es";
    skvt2.type = TYPE_ELEMENT_STATE;
    skvs_t[1] = skvt2;

    skvt3.key = "coj";
    skvt3.type = TYPE_INT;
    skvt3.value.vi32 = 11;

    skvt4.key = "cok";
    skvt4.type = TYPE_INT;
    skvt4.value.vi32 = 45;

    skvt5.key = "col";
    skvt5.type = TYPE_INT;
    skvt5.value.vi32 = 514;

    skvt6.key = "com";
    skvt6.type = TYPE_INT;
    skvt6.value.vi32 = 1919;

    skvs_t[2] = skvt3;
    skvs_t[3] = skvt4;
    skvs_t[4] = skvt5;
    skvs_t[5] = skvt6;
 
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // tft180_show_gray_image (0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, 150);
            tft180_displayimage03x((const uint8* )mt9v03x_image, SCREEN_WIDTH, SCREEN_HEIGHT);
            image_boundary_process();
            // image_process();
            switch_trackline();
            process_data();
            
            skvt3.value.vi32 = cross_out_j;
            skvt4.value.vi32 = cross_out_k;
            skvt5.value.vi32 = cross_out_l;
            skvt6.value.vi32 = cross_out_m;

            skvs_t[2] = skvt3;
            skvs_t[3] = skvt4;
            skvs_t[4] = skvt5;
            skvs_t[5] = skvt6;
            // printf("%d, %d, %f, %f\n", encoder_data_l, encoder_data_r, motor_input_l, motor_input_r);
            // skvt3.value.vi32 = out_hrl;
            // skvt4.value.vi32 = out_hrr;
            // skvt5.value.vi32 = out_j;
            // skvt6.value.vi32 = out_k;
            // skvt7.value.vi32 = out_rs;
            // skvs_t[2] = skvt3;
            // skvs_t[3] = skvt4;
            // skvs_t[4] = skvt5;
            // skvs_t[5] = skvt6;
            // skvs_t[6] = skvt7;
            show_skvs(&skvs_t, SKVS_T_LENGHT);

            show_line();
            show_mark();
            // print_sidelines();
            mt9v03x_finish_flag = 0;
        }
    }
}
void test_ser_motor_run(void) {
    struct ShowKeyValue skvs_t1[SKVS_T1_LENGHT];
    struct ShowKeyValue skvt1, skvt2, skvt3, skvt4;

    skvt1.key = "v";
    skvt1.type = TYPE_UINT;
    skvt1.value.vu32 = 6;

    skvt2.key = "sm_in";
    skvt2.type = TYPE_DOUBLE;
    skvt2.value.d = 11;

    skvt3.key = "p_i";
    skvt3.type = TYPE_DOUBLE;
    skvt3.value.d = 45;

    skvt4.key = "p_o";
    skvt4.type = TYPE_DOUBLE;
    skvt4.value.d = 14;

    skvs_t1[0] = skvt1;
    skvs_t1[1] = skvt2;
    skvs_t1[2] = skvt3;
    skvs_t1[3] = skvt4;
     while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(mt9v03x_finish_flag) {
            // tft180_show_gray_image (0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, 150);
            tft180_displayimage03x((const uint8* )mt9v03x_image, SCREEN_WIDTH, SCREEN_HEIGHT);
            image_boundary_process();
            switch_trackline();
            process_data();
            
            // printf("%d, %d, %f, %f\n", encoder_data_l, encoder_data_r, motor_input_l, motor_input_r);
            skvt2.value.d = server_motor_input;
            skvt3.value.d = sm_pid.err_now;
            skvt4.value.d = sm_pid.output;
            skvs_t1[1] = skvt2;
            skvs_t1[2] = skvt3;
            skvs_t1[3] = skvt4;
            show_skvs(&skvs_t1, SKVS_T1_LENGHT);

            show_line();
            show_mark();
            mt9v03x_finish_flag = 0;
        }
    }


}
void test_wireless_pic(void) {
    while (TRUE)
    {
        // sendimg(mt9v03x_image, MT9V03X_W, MT9V03X_H);
        send_buff++;
        wireless_uart_send_buffer(&send_buff, 1);
        system_delay_ms(1000);
    }
}

int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������
    #ifdef TEST_AND_COMMON_RUN
        init_all();
    #elif defined TEST_WIRELESS_PIC
        test_wireless_pic_init();
    #endif

    // test_wireless_pic_init();

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    #ifdef TEST_AND_COMMON_RUN
        if (IS_TEST){
            test_run();
        } else {
            common_run();
        }
    #elif defined TEST_WIRELESS_PIC
        test_wireless_pic();
    #endif
    
    return 0;
}

#pragma section all restore


// **************************** �������� ****************************
