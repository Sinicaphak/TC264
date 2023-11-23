//ifdef
#ifndef _INITIALIZE_H_
#define _INITIALIZE_H_
// �����ȫ�ŵ�Ϊtrue, ����Ϊfalse
#define IS_FULL_BRIDGE (false)

// ȫ�ŵ��������pwm����
#define FULL_BRIDGE_LEFT_DIR (P21_2)
#define FULL_BRIDGE_LEFT_PWM (ATOM0_CH1_P21_3)
#define FULL_BRIDGE_RIGHT_DIR (P21_4)
#define FULL_BRIDGE_RIGHT_PWM (ATOM0_CH3_P21_5)
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
#define ENCODER_LEFT                   (TIM2_ENCODER)
#define ENCODER_LEFT_A                 (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_LEFT_B                 (TIM2_ENCODER_CH2_P33_6)

#define ENCODER_RIGHT                   (TIM5_ENCODER)
#define ENCODER_RIGHT_A                 (TIM5_ENCODER_CH1_P10_3)
#define ENCODER_RIGHT_B                 (TIM5_ENCODER_CH2_P10_1)

/* #define ENCODER_3                   (TIM4_ENCODER)
#define ENCODER_3_A                 (TIM4_ENCODER_CH1_P02_8)
#define ENCODER_3_B                 (TIM4_ENCODER_CH2_P00_9)

#define ENCODER_4                   (TIM6_ENCODER)
#define ENCODER_4_A                 (TIM6_ENCODER_CH1_P20_3)
#define ENCODER_4_B                 (TIM6_ENCODER_CH2_P20_0) */

void init_all(void);

// endif
#endif
