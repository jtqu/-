#ifndef HEAD
#define HEAD
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<windows.h>
typedef struct house{
	char num[10];	//房屋编号 
	char name[30];	//房屋名称 
	char buyer[30];	//购买人 
	char tel[11];	//购买人电话 
	double area;	//房屋面积 
	double money;	//购买金额
	struct house *next; //链域 
}house;

house *head;//在此定义表头head，保证整个程序都可使用 

house* house_in();	//将文件中的房屋信息存入房屋链表	
void start_show(void);	//开始界面 
void check_show(void);	//查找信息界面 
void modify_show(void);	//修改信息界面 
void seek_show(void);//查找房屋界面

void print(void);	//显示房屋信息 
void save(void);	//保存房屋信息至文本文件

void seek_buyer(void);//按购房人姓名查找
void seek_tel(void);//按购买人电话号码查找
void seek_area(void);//按房屋面积查找

void area_ascending(void);	//按房屋面积升序显示 
void money_ascending(void);	//按购房金额升序显示

void add_house(void);		//增加房屋信息
void modify_house(void);	//修改已有的房屋信息
void delete_house(void);	//删除已有的房屋信息


#endif
