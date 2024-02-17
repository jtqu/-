#include"head.h"

//将文件中的房屋信息存入房屋链表	 
house *house_in(){
	house *h,*p,*q;
	FILE *fp;
	h=0;
	if((fp=fopen("house.txt","r"))==0){
		printf("\t\t\t文件打开失败!\n");
		exit(0);
	}
	while(!feof(fp)){
		p=(house *)malloc(sizeof(house));
		p->next=0;
		fscanf(fp,"%s",p->num);
		fscanf(fp,"%s",p->name);
		fscanf(fp,"%s",p->buyer);
		fscanf(fp,"%s",p->tel);
		fscanf(fp,"%lf",&p->area);
		fscanf(fp,"%lf",&p->money);
		if(h==0){
			h=p;
			q=p;
		}else{
			q->next=p;
			q=p;
		}
	}
	fclose(fp);
	return h;
}


//保存房屋信息至文本文件
void save(void) {
	house* t = head->next;
	FILE *fp;
	if ((fp = fopen("house.txt", "w")) == 0) {
		printf("\t\t\t文件打开失败!\n");
		exit(1);
	}
	while (t->next) {
		fprintf(fp, "%s ", t->num);
		fprintf(fp, "%s ", t->name);
		fprintf(fp, "%s ", t->buyer);
		fprintf(fp, "%s ", t->tel);
		fprintf(fp, "%lf ", t->area);
		fprintf(fp, "%.2f", t->money);
		fprintf(fp, "\n");
		t = t->next;
	}
	fprintf(fp, "%s ", t->num);
	fprintf(fp, "%s ", t->name);
	fprintf(fp, "%s ", t->buyer);
	fprintf(fp, "%s ", t->tel);
	fprintf(fp, "%lf ", t->area);
	fprintf(fp, "%.2f", t->money);
	fclose(fp);
	printf("\n\t\t\t文件已保存!");
	Sleep(500);
}


//显示房屋信息
void print(void){
	house *p;
	p=head->next;
	printf("\t**************************************************\n");
	printf("%-12s%-12s%-12s%-16s%-10s%-10s",
		"编号","房屋名称","购买人姓名","购买人电话","房屋面积","购房金额");
	printf("\n");
	while(p){
		printf("%-12s",p->num);
		printf("%-12s",p->name);
		printf("%-12s",p->buyer);
		printf("%-16s",p->tel);
		printf("%-10.2f",p->area);
		printf("%-10.2f\n",p->money);
		p=p->next;
	}
	printf("\t***************************************************\n");
	system("pause");
}




//按房屋面积升序显示
void area_ascending(){
	house *p1,*p2,*p3,*t,*end=NULL;
	p1=head;
	if(head->next==0){
		printf("\t\t\t暂无房屋信息\n");
		return;
	}
	if(head->next->next==0){
		return;
	}
	while(head->next!=end){
		p1=head;
		p2=p1->next;
		p3=p2->next;
		while(p3!=end){
			if(p2->area > p3->area){
				p1->next=p2->next;
				p2->next=p3->next;
				p3->next=p2;
				t=p2;
				p2=p3;
				p3=t;
			}
			p1=p1->next;
			p2=p2->next;
			p3=p3->next;
		}
		end=p2;
	}
	print();
}


//按房屋金额升序显示
void money_ascending(){
	house* p1, * p2, * p3, * t, * end = NULL;
	p1 = head;
	if (head->next == 0) {
		printf("\t\t\t暂无房屋信息\n");
		return;
	}
	if (head->next->next == 0) {
		return;
	}
	while (head->next != end) {
		p1 = head;
		p2 = p1->next;
		p3 = p2->next;
		while (p3 != end) {
			if (p2->money > p3->money) {
				p1->next = p2->next;
				p2->next = p3->next;
				p3->next = p2;
				t = p2;
				p2 = p3;
				p3 = t;
			}
			p1 = p1->next;
			p2 = p2->next;
			p3 = p3->next;
		}
		end = p2;
	}
	print();
}

//按购买人查找
void seek_buyer() {
	house* t = head->next;
	char seek_in[30];
	printf("\n\t\t请输入要查找的购买人姓名:");
	scanf("%s", seek_in);
	while (t) {
		if (strcmp(t->buyer, seek_in)==0) {
			break;
		}
		t = t->next;
	}
	if (t == 0) {
		printf("\n\t\t\t未查找到相关信息！\n");
	}
	else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"编号", "房屋名称", "购买人姓名", "购买人电话", "房屋面积", "购房金额");
		printf("\n");
		printf("%-12s", t->num);
		printf("%-12s", t->name);
		printf("%-12s", t->buyer); 
		printf("%-16s", t->tel);
		printf("%-10.2f", t->area);
		printf("%-10.2f\n", t->money);
		printf("\t***************************************************\n");
	}
	system("pause");
}

//按电话查找
void seek_tel() {
	house* t = head->next;
	char seek_in[30];
	printf("\n\t\t请输入要查找的购买人电话:");
	scanf("%s", seek_in);
	while (t) {
		if (strcmp(t->tel, seek_in) == 0) {
			break;
		}
		t = t->next;
	}
	if (t==0) {
		printf("\n\t\t\t未查找到相关信息！\n");
	} else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"编号", "房屋名称", "购买人姓名", "购买人电话", "房屋面积", "购房金额");
		printf("\n");
		printf("%-12s", t->num);
		printf("%-12s", t->name);
		printf("%-12s", t->buyer);
		printf("%-16s", t->tel);
		printf("%-10.2f", t->area);
		printf("%-10.2f\n", t->money);
		printf("\t***************************************************\n");
	}

	
	system("pause");
}



//按面积查找
void seek_area() {
	house* t = head->next;
	double seek_in;
	printf("\n\t\t请输入要查找的房屋面积:");
	scanf("%lf", &seek_in);
	while (t) {
		if (t->area==seek_in ) {
			break;
		}
		t = t->next;
	}
	if (t == 0) {
		printf("\n\t\t\t未查找到相关信息！\n");
	}
	else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"编号", "房屋名称", "购买人姓名", "购买人电话", "房屋面积", "购房金额");
		printf("\n");
		printf("%-12s", t->num);
		printf("%-12s", t->name);
		printf("%-12s", t->buyer);
		printf("%-16s", t->tel);
		printf("%-10.2f", t->area);
		printf("%-10.2f\n", t->money);
		printf("\t***************************************************\n");
	}
	system("pause");
}

//增加房屋信息
void add_house(void) {
	house* new = (house*)malloc(sizeof(house));
	new->next = head->next;

	printf("\n\t\t\t请输入以下信息:\n");
	printf("\t\t房屋编号:");
	scanf("%s", new->num);
	printf("\n\t\t房屋名称:");
	scanf("%s", new->name);
	printf("\n\t\t购买人姓名:");
	scanf("%s", new->buyer);
	printf("\n\t\t购买人电话:");
	scanf("%s", new->tel);
	printf("\n\t\t房屋面积:");
	scanf("%lf", &new->area);
	printf("\n\t\t购房金额:");
	scanf("%lf", &new->money);
	head->next = new;
	system("pause");
}

//修改已有的房屋信息
void modify_house(void) {
	char modify[10];
	char modify2;
	house* t = head->next;
	system("color b0");
	system("CLS");
	printf("\n\t\t\t以下为现有的房屋信息\n");
	print();
	printf("\n\t\t请输入要修改的房屋编号:");
	scanf("%s", modify);
	while (t) {
		if (strcmp(modify, t->num) == 0) {
			break;
		}
		t = t->next;
	}
	printf("\t**************************************************\n");
	printf("\t\t\t1)编号");
	printf("\n\t\t\t2)房屋名称");
	printf("\n\t\t\t3)购买人信息");
	printf("\n\t\t\t4)购买人电话");
	printf("\n\t\t\t5)房屋面积");
	printf("\n\t\t\t6)购房金额");
	printf("\n\t**************************************************\n");
	printf("\n\t\t\t请输入你要修改的内容编号:");
	again:
	scanf(" %c", &modify2);
	switch (modify2) {
		case '1':printf("\n\t请输入新编号:");
				scanf("%s", t->num); break;
		case '2':printf("\n\t请输入新房屋名称:");
				scanf("%s", t->name); break;
		case '3':printf("\n\t请输入新购买人姓名:");
				scanf("%s", t->buyer); break;
		case '4':printf("\n\t请输入新购买人电话:");
				scanf("%s", t->tel); break;
		case '5':printf("\n\t请输入新房屋面积:");
				scanf("%lf", &t->area); break;
		case '6':printf("\n\t请输入新购房金额:");
				scanf("%lf", &t->money); break;
		default:printf("输入错误，请重新正确输入:"); goto again; break;
	}
	printf("\n\t\t\t房屋信息已修改完成！");
	system("pause");
}

//删除已有的房屋信息
void delete_house(void) {
	char del[10];
	house* t = head;
	house* t_del = head->next;	//t_del为所需删除的结点，t为所需删除结点的前一个结点
	system("color b0");
	system("CLS");
	printf("\n\t\t\t以下为现有的房屋信息\n");
	print();
	printf("\n\t\t请输入要删除的房屋编号:");
	scanf("%s", del);
	while (t_del) {
		if (strcmp(del, t_del->num) == 0) {
			break;
		}
		t_del = t_del->next;
		t = t->next;
	}

	if (t_del== 0) {
		t->next = 0;
		printf("\n\t\t未找到需要删除的房屋信息!");
	}
	else {
		t->next = t_del->next;
		printf("\n\t\t房屋信息已删除！\n");
		free(t_del);
	}
	system("pause");
}