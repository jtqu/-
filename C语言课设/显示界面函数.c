#include "head.h"

//��ʼ����
void start_show(void){
	system("color b0");
	system("CLS");
	printf("\n\n\n\n\t\t\t\t���ݹ���ϵͳ");
	printf("\n\t\t\t*************************\n\n");
	printf("\t\t\t\t1)�鿴��Ϣ\n");
	printf("\t\t\t\t2)�޸���Ϣ\n");
	printf("\t\t\t\t0)�˳�ϵͳ\n");
	printf("\n\t\t\t*************************\n\n");
} 


//�鿴���� 
void check_show(void){
	char checkin='1';
	while(checkin!='0'){
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t��Ϣ�鿴");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)���ҷ���\n");
		printf("\t\t\t2)���������������ʾ\n");
		printf("\t\t\t3)�����ݽ��������ʾ\n");
		printf("\t\t\t0)����\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c",&checkin);
		//getchar();
		switch(checkin){
			case '1':	seek_show();break;
			case '2':	area_ascending();break;
			case '3':	money_ascending(); break;
			case '0':	break;
			default :printf("\t\t\t�����������������\n");Sleep(500);break;
		}
	}
}

//�޸Ľ��� 
void modify_show(void){
	
	char modifyin = '1';
	while (modifyin != '0') {
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t��Ϣ�޸�");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)���ӷ�����Ϣ\n");
		printf("\t\t\t2)�޸ķ�����Ϣ\n");
		printf("\t\t\t3)ɾ��������Ϣ\n");
		printf("\t\t\t0)����\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c", &modifyin);
		//getchar();
		switch (modifyin) {
		case '1':	add_house(); break;
		case '2':	modify_house(); break;
		case '3':	delete_house(); break;
		case '0':	break;
		default:printf("\t\t\t�����������������\n"); Sleep(500); break;
		}
	}
}

//���ҽ���
void seek_show() {
	char seekin = '1';
	while (seekin != '0') {
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t��Ϣ����");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)����������������\n");
		printf("\t\t\t2)�������˵绰���������\n");
		printf("\t\t\t3)�������������\n");
		printf("\t\t\t0)����\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c", &seekin);

		switch (seekin) {
		case '1':	seek_buyer(); break;
		case '2':	seek_tel(); break;
		case '3':	seek_area(); break;
		case '0':	break;
		default:printf("\t\t\t�����������������\n"); Sleep(500); break;
		}
	}
}

