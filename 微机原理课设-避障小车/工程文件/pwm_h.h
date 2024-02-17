#ifndef    _PWM_H_
#define    _PWM_H_

#include"c8051f360.h"


/*************************************************************************************************
*****           配置所有电机要使用的端口为推挽输出，使能PCA交叉开关允许位
*****			电机速度控制线：CPP0 ----- P0.6    CPP1 ----- P0.7    CPP2 ----- P1.0	CPP3 ----- P1.1
*****						   	CPP4 ----- P1.2	  CPP5 ----- P1.3
*****			电机方向控制性：DIR0 ----- P3.5	  DIR1 ----- P1.4	 DIR2 ----- P1.5	DIR3 ----- P1.6
*****		   				    DIR4 ----- P3.6	  DIR5 ----- 由主板JP1端口跳接电源和地来硬件切换方向							
**************************************************************************************************/

sbit DIR0=P3^5;
sbit DIR1=P1^4;
sbit DIR2=P1^5;
sbit DIR3=P1^6;
sbit DIR4=P3^6;
//第5路电机方向不受控制，直接跳电源或地

void DC_Motor(unsigned char motor_num,
              unsigned char direction, unsigned char motor_speed);
void PWM_Init(void);


#endif