#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_


#include"C8051F360.h"
#include <string.h>
#include <stdio.h>

#define OUT   1
#define IN   0

#define LEFT_F   1
#define LEFT_B   3
#define RIGHT_F   2
#define RIGHT_B   4

#define STOP   1
#define GOING  0
#define BACK   2

void TurnOnLight();
void TurnOffLight();
void LightTestCounter();
void LightTestSensor();

unsigned char GetInfo();



void Test();
void Voice_Test();
void SensorTest();
void MotoTest();
void SpeechTest();
void LCD12864Test();
void Voice_Start();
void Break_Fire_Test(unsigned char direction);

extern void Delay_ms(unsigned int);
extern void Delay(unsigned int);

extern void SystemInit(void);

extern void SendChiGB(char *Data);

extern void DodgeObstruction(void);
extern void AppFireTest(void);

extern unsigned char GetIR_Distance(unsigned char AD_port);
extern unsigned int GetIRDistance(unsigned char AD_port);
extern void LcdDesppayInt(unsigned int uiData);
extern void DesppayChar(unsigned char uiData);
extern void LCD_Display(unsigned char * tab,unsigned char add,
            unsigned int data_input);
extern void LcdDisplay12864(unsigned char row,unsigned char col,
                unsigned char * str,bit onoff,unsigned int data_input);
extern void Display_Char12864(unsigned char row,unsigned char col,
                unsigned char * str,unsigned char data_input);
extern void DisplayChinese(unsigned char row,unsigned char col,
               unsigned char cara_one,unsigned char cara_two);

extern void DC_Motor(unsigned char motor_num,unsigned char direction,
                     unsigned char motor_speed);

extern unsigned char GetIR_EyesData(unsigned char I2cAdr,
                     unsigned char channel,unsigned char command);

extern void Speech(unsigned char *buf, unsigned char len);

extern void Wait(unsigned int delay);

#endif