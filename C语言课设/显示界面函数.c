#include "head.h"

//开始界面
void start_show(void){
	system("color b0");
	system("CLS");
	printf("\n\n\n\n\t\t\t\t房屋管理系统");
	printf("\n\t\t\t*************************\n\n");
	printf("\t\t\t\t1)查看信息\n");
	printf("\t\t\t\t2)修改信息\n");
	printf("\t\t\t\t0)退出系统\n");
	printf("\n\t\t\t*************************\n\n");
} 


//查看界面 
void check_show(void){
	char checkin='1';
	while(checkin!='0'){
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t信息查看");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)查找房屋\n");
		printf("\t\t\t2)按房屋面积升序显示\n");
		printf("\t\t\t3)按房屋金额升序显示\n");
		printf("\t\t\t0)返回\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c",&checkin);
		//getchar();
		switch(checkin){
			case '1':	seek_show();break;
			case '2':	area_ascending();break;
			case '3':	money_ascending(); break;
			case '0':	break;
			default :printf("\t\t\t输入错误，请重新输入\n");Sleep(500);break;
		}
	}
}

//修改界面 
void modify_show(void){
	
	char modifyin = '1';
	while (modifyin != '0') {
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t信息修改");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)增加房屋信息\n");
		printf("\t\t\t2)修改房屋信息\n");
		printf("\t\t\t3)删除房屋信息\n");
		printf("\t\t\t0)返回\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c", &modifyin);
		//getchar();
		switch (modifyin) {
		case '1':	add_house(); break;
		case '2':	modify_house(); break;
		case '3':	delete_house(); break;
		case '0':	break;
		default:printf("\t\t\t输入错误，请重新输入\n"); Sleep(500); break;
		}
	}
}

//查找界面
void seek_show() {
	char seekin = '1';
	while (seekin != '0') {
		system("color b0");
		system("CLS");
		printf("\n\n\n\n\t\t\t\t信息查找");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t1)按购房人姓名查找\n");
		printf("\t\t\t2)按购房人电话号码序查找\n");
		printf("\t\t\t3)按房屋面积查找\n");
		printf("\t\t\t0)返回\n");
		printf("\n\t\t\t*************************\n\n");
		printf("\t\t\t");
		scanf(" %c", &seekin);

		switch (seekin) {
		case '1':	seek_buyer(); break;
		case '2':	seek_tel(); break;
		case '3':	seek_area(); break;
		case '0':	break;
		default:printf("\t\t\t输入错误，请重新输入\n"); Sleep(500); break;
		}
	}
}

