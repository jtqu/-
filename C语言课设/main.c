#include "head.h"

int main(int argc, char *argv[]) {
	char startin='1';
	head=(house *)malloc(sizeof(house)); //创建空表头 
	head->next=house_in();

	while(startin!='0'){
		start_show();
		printf("\n\t\t\t");
		scanf(" %c",&startin);
		
		switch(startin){
			case '1':check_show();break;
			case '2':modify_show();break;
			case '0':goto out;break;
			default :printf("\t\t\t输入错误，请重新输入:\n\t\t\t");break;
		}
		
	}


	system("pause");
	out:	//初始菜单页面输入0时跳到此处退出系统 
	save();
	return 0;
}
