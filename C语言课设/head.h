#ifndef HEAD
#define HEAD
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<windows.h>
typedef struct house{
	char num[10];	//���ݱ�� 
	char name[30];	//�������� 
	char buyer[30];	//������ 
	char tel[11];	//�����˵绰 
	double area;	//������� 
	double money;	//������
	struct house *next; //���� 
}house;

house *head;//�ڴ˶����ͷhead����֤�������򶼿�ʹ�� 

house* house_in();	//���ļ��еķ�����Ϣ���뷿������	
void start_show(void);	//��ʼ���� 
void check_show(void);	//������Ϣ���� 
void modify_show(void);	//�޸���Ϣ���� 
void seek_show(void);//���ҷ��ݽ���

void print(void);	//��ʾ������Ϣ 
void save(void);	//���淿����Ϣ���ı��ļ�

void seek_buyer(void);//����������������
void seek_tel(void);//�������˵绰�������
void seek_area(void);//�������������

void area_ascending(void);	//���������������ʾ 
void money_ascending(void);	//���������������ʾ

void add_house(void);		//���ӷ�����Ϣ
void modify_house(void);	//�޸����еķ�����Ϣ
void delete_house(void);	//ɾ�����еķ�����Ϣ


#endif
