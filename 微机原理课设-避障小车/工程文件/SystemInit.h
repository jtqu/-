#ifndef  _SYSTEM_INIT_H_
#define  _SYSTEM_INIT_H_

//-----------------------------------------------------------------------------
// 包含文件
//-----------------------------------------------------------------------------
#include "C8051F360.h"
#include "Sound.h"

//-----------------------------------------------------------------------------
// 函数原型
//-----------------------------------------------------------------------------

void SystemInit(void);

void InternalCrystalInit(void);

void Delay(unsigned int);

extern void Pin_Config(void);
extern void LCD_Init(void);
extern void ADC_Init(void);
extern void PWM_Init(void);
extern void LCD12864_Init(void);


#endif