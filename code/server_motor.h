//ifdef
#ifndef _SERVER_MOTOR_H_
#define _SERVER_MOTOR_H_
//todo 下面这段靠谱吗?
// ------------------ 舵机占空比计算方式 ------------------
//
// 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
//
// 那么不同频率下的占空比计算方式就是
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ 舵机占空比计算方式 ------------------

// 舵机左值 ??? 右值 ?? 中值 ?
#define SERVER_DUTY_MAX (920)
#define SERVER_DUTY_MIDDLE (820)
#define SERVER_DUTY_MIN (710)

//endif
#endif
