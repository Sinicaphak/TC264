//ifdef
#ifndef _SERVER_MOTOR_H_
#define _SERVER_MOTOR_H_
//todo ������ο�����?
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
//
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
//
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------

// �����ֵ ??? ��ֵ ?? ��ֵ ?
#define SERVER_DUTY_MAX (920)
#define SERVER_DUTY_MIDDLE (820)
#define SERVER_DUTY_MIN (710)

//endif
#endif
