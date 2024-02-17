
/**********************************************************************************************************
**** 文件名：pwm_c.c
**** 
**** 文件描述：PWM电机调速和转向函数库
****		   电机速度控制线：CPP0 ----- P0.6    CPP1 ----- P0.7    CPP2 ----- P1.0	CPP3 ----- P1.1
****						   CPP4 ----- P1.2	  CPP5 ----- P1.3
****		   电机方向控制性：DIR0 ----- P3.5	  DIR1 ----- P1.4	 DIR2 ----- P1.5	DIR3 ----- P1.6
****		   				   DIR4 ----- P3.6	  DIR5 ----- 由主板JP1端口跳接电源和地来硬件切换方向


****		   电机方向控制性：DIR0 ----- P3.1	  DIR1 ----- P1.4	 DIR2 ----- P1.5	DIR3 ----- P1.6
****		   				   DIR4 ----- P3.2	  DIR5 ----- 由主板JP1端口跳接电源和地来硬件切换方向        2014.7.28主板
****			
****
**** 创建人：FeiChen
**** 
**** 版本号：1.0
**** 
**** 修改记录：
**** 
**** 
****
***********************************************************************************************************/



#include"pwm_h.h"
/*************************************************************************************************
*****
***** 函数名：void PWM_Init()
*****
***** 入口参数：无
*****
*****
***** 功能描述：PWM初始化函数：设置8位PWM模式，比较器功能使能，PWM使能，允许PCA计数
*****							初始化结尾处关闭电机转动
*****           PWM端口初始化，配置所有电机要使用的端口为推挽输出，使能PCA交叉开关允许位
*****			电机速度控制线：CPP0 ----- P0.6    CPP1 ----- P0.7    CPP2 ----- P1.0	CPP3 ----- P1.1
*****						   	CPP4 ----- P1.2	  CPP5 ----- P1.3
*****			电机方向控制性：DIR0 ----- P3.5	  DIR1 ----- P1.4	 DIR2 ----- P1.5	DIR3 ----- P1.6
*****		   				    DIR4 ----- P3.6	  DIR5 ----- 由主板JP1端口跳接电源和地来硬件切换方向							
*****		   
*****
***** 返回值：无
*****
***** 作者：FeiChen
**************************************************************************************************/

void PWM_Init()
{
	unsigned char SFRPAGE_save = SFRPAGE; 


	SFRPAGE = CONFIG_PAGE;             
	
	PCA0MD = 0x08;              //PCA计数时钟源采用系统时钟

	PCA0CPM0 = 0x42;            //6路PCA为8位PWM 模式，比较器功能使能，PWM使能
	PCA0CPM1 = 0x42;
	PCA0CPM2 = 0x42;
	PCA0CPM3 = 0x42;
	PCA0CPM4 = 0x42;
	PCA0CPM5 = 0x42;

	PCA0CPH0 = 0x00;			//配置PCA占空比，0(最大占空比)~0xFF(最小占空比)
	PCA0CPH1 = 0x00;			//
	PCA0CPH2 = 0x00;			//针对大功率电机控制板
	PCA0CPH3 = 0x00;
	PCA0CPH4 = 0x00;
	PCA0CPH5 = 0x00;

	CR = 1;        				//允许PCA计数，定时

	SFRPAGE = SFRPAGE_save; 
	
	DC_Motor(1,1,0);			//初始化完成后设置各路电机静止
	DC_Motor(2,1,0);
	DC_Motor(3,1,0);
	DC_Motor(4,1,0); 
	DC_Motor(5,1,0);
	DC_Motor(6,1,0);
             
}

/*************************************************************************************************
*****
***** 函数名：void DC_Motor(unsigned char motor_num,unsigned char direction, unsigned char motor_speed)
*****
*****
***** 入口参数：motor_num 电机号，使能第几路电机输出。取值为1-6，共有6路电机输出可用
*****			
*****			direction 电机方向选择，取值0——正转，1——停止，2——反转
*****			motor_speed 电机速度选择，取值范围：0-100，0——停止，100——最大速度
*****
*****
***** 功能描述：PWM端口初始化，配置所有电机要使用的端口为推挽输出，使能PCA交叉开关允许位
*****			电机速度控制线：CPP0 ----- P0.6    CPP1 ----- P0.7    CPP2 ----- P1.0	CPP3 ----- P1.1
*****						   	CPP4 ----- P1.2	  CPP5 ----- P1.3
*****			电机方向控制性：DIR0 ----- P3.5	  DIR1 ----- P1.4	 DIR2 ----- P1.5	DIR3 ----- P1.6
*****		   				    DIR4 ----- P3.6	  DIR5 ----- 由主板JP1端口跳接电源和地来硬件切换方向							
*****		   
*****
***** 返回值：无 
*****
***** 作者：FeiChen
**************************************************************************************************/
/******************************************************************************
//! 函数名：void DC_Motor(uc motor_num,uc direction, uc motor_speed)
//! 函数功能：改变PWM占空比
******************************************************************************/
void 
DC_Motor(unsigned char motor_num,unsigned char direction, unsigned char motor_speed)
{
	unsigned char SFRPAGE_save = SFRPAGE; 
	
	SFRPAGE = CONFIG_PAGE;

	//ucMotorSpeed = (float)(motor_speed)/100;
	//若电机速度为0，则直接停止PCA中PCA0PHn寄存器，即，直接关闭电机转动
	//此时不管电机的方向如何，均是停止转动电机
	if(!motor_speed)
	{
		switch(motor_num)
		{
			case 1:
			
				PCA0CPH0 = 255;		//针对大功率电机控制板

				break;

			case 2:
		
				PCA0CPH1 = 255;

				break;

			case 3:
			
				PCA0CPH2 = 255;

				break;

			case 4:
			
			
				PCA0CPH3 = 255;

				break;

	        case 5:		
			
				PCA0CPH4 = 255;

				break;

			case 6:		
		
				PCA0CPH5 = 255;

				break;

		    default: break;
		}
	}

	else 

	//电机速度控制
	//首先确定哪路电机，然后确定对应电机速度的大小
	
	switch(motor_num)
	{
		case 1:
			
			PCA0CPH0 = 255-(motor_speed+116);
			break;

		case 2:
		 
			PCA0CPH1 = 255-(motor_speed+116);       // (motor_speed+125)
			break;

		case 3:
			
			PCA0CPH2 =255-(motor_speed+116);
			break;

		case 4:
				
			PCA0CPH3 = 255-(motor_speed+116);		//(motor_speed+125)
			break;

        case 5:		
			
			PCA0CPH4 =255-(motor_speed+116);
			break;

		case 6:		
		
			PCA0CPH5 = 255- (motor_speed+116);
			break;

	    default: break;
	}
	
	
	switch(direction)
	{
		//电机正向转动模式，针对大功率电机控制板
		case 0: 

			if(motor_num==1) DIR0=0; //P3.5 = 0,即DIR0置0      主板版本号：2012 3 28
			if(motor_num==2) DIR1=0; //P1.4 = 0,即DIR1置0
			if(motor_num==3) DIR2=0; //P1.5 = 0,即DIR2置0
			if(motor_num==4) DIR3=0; //P1.6 = 0,即DIR3置0
			if(motor_num==5) DIR4=0; //P3.6 = 0,即DIR4置0
		
			break;
			
			
		//停止模式，针对大功率电机控制板	
		case 1: 

			if(motor_num==1) PCA0CPH0 = 255;
			if(motor_num==2) PCA0CPH1 = 255;
			if(motor_num==3) PCA0CPH2 = 255;
			if(motor_num==4) PCA0CPH3 = 255;
			if(motor_num==5) PCA0CPH4 = 255;
			if(motor_num==6) PCA0CPH5 = 255;	//DIR5的方向有主板上JP1端口跳接电源和地来实现
										    	//但停止是通过关闭PCA0计数寄存器实现的	
			break;
			

		//电机反向转动模式，针对大功率电机控制板
		case 2: 
		
			if(motor_num==1) DIR0=1;  //P3.5 = 1,即DIR0置1；       主板版本号：2012 3 28
			if(motor_num==2) DIR1=1;  //P1.4 = 1,即DIR1置1；
			if(motor_num==3) DIR2=1;  //P1.5 = 1,即DIR2置1；
			if(motor_num==4) DIR3=1;  //P1.6 = 1,即DIR3置1；
			if(motor_num==5) DIR4=1;  //P3.6 = 1,即DIR4置1；

			break;

		default: break;
}

	SFRPAGE = SFRPAGE_save;
}
/**********************************************************************************
//! 文件结束
**********************************************************************************/
 

	
