//ifdef
#ifndef _INITIALIZE_H_
#define _INITIALIZE_H_
// �����ȫ�ŵ�Ϊtrue, ����Ϊfalse
#define IS_FULL_BRIDGE (true)

// ȫ�ŵ��������pwm����
#define FULL_BRIDGE_LEFT_DIR (P21_4)
#define FULL_BRIDGE_LEFT_PWM (ATOM0_CH3_P21_5)
#define FULL_BRIDGE_RIGHT_DIR (P21_2)
#define FULL_BRIDGE_RIGHT_PWM (ATOM0_CH1_P21_3)
// ��ת��ת
#define FULL_MOTOR_FORWARD (GPIO_LOW)
#define FULL_MOTOR_BACKWARD (GPIO_HIGH)

// ���ŵ������ת����
#define HALF_BRIDGE_LEFT_A (ATOM0_CH0_P21_2)
#define HALF_BRIDGE_LEFT_B (ATOM0_CH1_P21_3)
#define HALF_BRIDGE_RIGHT_A (ATOM0_CH2_P21_4)
#define HALF_BRIDGE_RIGHT_B (ATOM0_CH3_P21_5)

// ���
// �������
#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)    
// Ƶ��
#define SERVO_MOTOR_FREQ            (50)

// ������
// #define ENCODER_LEFT                   (TIM2_ENCODER)
// #define ENCODER_LEFT_A                 (TIM2_ENCODER_CH1_P33_7)
// #define ENCODER_LEFT_B                 (TIM2_ENCODER_CH2_P33_6)

// #define ENCODER_RIGHT                   (TIM4_ENCODER)
// #define ENCODER_RIGHT_A                 (TIM4_ENCODER_CH1_P02_8)
// #define ENCODER_RIGHT_B                 (TIM4_ENCODER_CH2_P00_9)
#define ENCODER_RIGHT                   (TIM2_ENCODER)
#define ENCODER_RIGHT_A                (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_RIGHT_B               (TIM2_ENCODER_CH2_P33_6)

#define ENCODER_LEFT                   (TIM4_ENCODER)
#define ENCODER_LEFT_A                 (TIM4_ENCODER_CH1_P02_8)
#define ENCODER_LEFT_B                 (TIM4_ENCODER_CH2_P00_9)

void init_all(void);
// void init_sideline(void);

// endif
#endif
