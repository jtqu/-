#include "head.h"

int main(int argc, char *argv[]) {
	char startin='1';
	head=(house *)malloc(sizeof(house)); //�����ձ�ͷ 
	head->next=house_in();

	while(startin!='0'){
		start_show();
		printf("\n\t\t\t");
		scanf(" %c",&startin);
		
		switch(startin){
			case '1':check_show();break;
			case '2':modify_show();break;
			case '0':goto out;break;
			default :printf("\t\t\t�����������������:\n\t\t\t");break;
		}
		
	}


	system("pause");
	out:	//��ʼ�˵�ҳ������0ʱ�����˴��˳�ϵͳ 
	save();
	return 0;
}
