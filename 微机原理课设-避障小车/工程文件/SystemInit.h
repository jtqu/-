#ifndef  _SYSTEM_INIT_H_
#define  _SYSTEM_INIT_H_

//-----------------------------------------------------------------------------
// �����ļ�
//-----------------------------------------------------------------------------
#include "C8051F360.h"
#include "Sound.h"

//-----------------------------------------------------------------------------
// ����ԭ��
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