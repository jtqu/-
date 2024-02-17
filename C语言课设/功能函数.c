#include"head.h"

//���ļ��еķ�����Ϣ���뷿������	 
house *house_in(){
	house *h,*p,*q;
	FILE *fp;
	h=0;
	if((fp=fopen("house.txt","r"))==0){
		printf("\t\t\t�ļ���ʧ��!\n");
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


//���淿����Ϣ���ı��ļ�
void save(void) {
	house* t = head->next;
	FILE *fp;
	if ((fp = fopen("house.txt", "w")) == 0) {
		printf("\t\t\t�ļ���ʧ��!\n");
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
	printf("\n\t\t\t�ļ��ѱ���!");
	Sleep(500);
}


//��ʾ������Ϣ
void print(void){
	house *p;
	p=head->next;
	printf("\t**************************************************\n");
	printf("%-12s%-12s%-12s%-16s%-10s%-10s",
		"���","��������","����������","�����˵绰","�������","�������");
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




//���������������ʾ
void area_ascending(){
	house *p1,*p2,*p3,*t,*end=NULL;
	p1=head;
	if(head->next==0){
		printf("\t\t\t���޷�����Ϣ\n");
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


//�����ݽ��������ʾ
void money_ascending(){
	house* p1, * p2, * p3, * t, * end = NULL;
	p1 = head;
	if (head->next == 0) {
		printf("\t\t\t���޷�����Ϣ\n");
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

//�������˲���
void seek_buyer() {
	house* t = head->next;
	char seek_in[30];
	printf("\n\t\t������Ҫ���ҵĹ���������:");
	scanf("%s", seek_in);
	while (t) {
		if (strcmp(t->buyer, seek_in)==0) {
			break;
		}
		t = t->next;
	}
	if (t == 0) {
		printf("\n\t\t\tδ���ҵ������Ϣ��\n");
	}
	else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"���", "��������", "����������", "�����˵绰", "�������", "�������");
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

//���绰����
void seek_tel() {
	house* t = head->next;
	char seek_in[30];
	printf("\n\t\t������Ҫ���ҵĹ����˵绰:");
	scanf("%s", seek_in);
	while (t) {
		if (strcmp(t->tel, seek_in) == 0) {
			break;
		}
		t = t->next;
	}
	if (t==0) {
		printf("\n\t\t\tδ���ҵ������Ϣ��\n");
	} else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"���", "��������", "����������", "�����˵绰", "�������", "�������");
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



//���������
void seek_area() {
	house* t = head->next;
	double seek_in;
	printf("\n\t\t������Ҫ���ҵķ������:");
	scanf("%lf", &seek_in);
	while (t) {
		if (t->area==seek_in ) {
			break;
		}
		t = t->next;
	}
	if (t == 0) {
		printf("\n\t\t\tδ���ҵ������Ϣ��\n");
	}
	else {
		printf("\t**************************************************\n");
		printf("%-12s%-12s%-12s%-16s%-10s%-10s",
			"���", "��������", "����������", "�����˵绰", "�������", "�������");
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

//���ӷ�����Ϣ
void add_house(void) {
	house* new = (house*)malloc(sizeof(house));
	new->next = head->next;

	printf("\n\t\t\t������������Ϣ:\n");
	printf("\t\t���ݱ��:");
	scanf("%s", new->num);
	printf("\n\t\t��������:");
	scanf("%s", new->name);
	printf("\n\t\t����������:");
	scanf("%s", new->buyer);
	printf("\n\t\t�����˵绰:");
	scanf("%s", new->tel);
	printf("\n\t\t�������:");
	scanf("%lf", &new->area);
	printf("\n\t\t�������:");
	scanf("%lf", &new->money);
	head->next = new;
	system("pause");
}

//�޸����еķ�����Ϣ
void modify_house(void) {
	char modify[10];
	char modify2;
	house* t = head->next;
	system("color b0");
	system("CLS");
	printf("\n\t\t\t����Ϊ���еķ�����Ϣ\n");
	print();
	printf("\n\t\t������Ҫ�޸ĵķ��ݱ��:");
	scanf("%s", modify);
	while (t) {
		if (strcmp(modify, t->num) == 0) {
			break;
		}
		t = t->next;
	}
	printf("\t**************************************************\n");
	printf("\t\t\t1)���");
	printf("\n\t\t\t2)��������");
	printf("\n\t\t\t3)��������Ϣ");
	printf("\n\t\t\t4)�����˵绰");
	printf("\n\t\t\t5)�������");
	printf("\n\t\t\t6)�������");
	printf("\n\t**************************************************\n");
	printf("\n\t\t\t��������Ҫ�޸ĵ����ݱ��:");
	again:
	scanf(" %c", &modify2);
	switch (modify2) {
		case '1':printf("\n\t�������±��:");
				scanf("%s", t->num); break;
		case '2':printf("\n\t�������·�������:");
				scanf("%s", t->name); break;
		case '3':printf("\n\t�������¹���������:");
				scanf("%s", t->buyer); break;
		case '4':printf("\n\t�������¹����˵绰:");
				scanf("%s", t->tel); break;
		case '5':printf("\n\t�������·������:");
				scanf("%lf", &t->area); break;
		case '6':printf("\n\t�������¹������:");
				scanf("%lf", &t->money); break;
		default:printf("���������������ȷ����:"); goto again; break;
	}
	printf("\n\t\t\t������Ϣ���޸���ɣ�");
	system("pause");
}

//ɾ�����еķ�����Ϣ
void delete_house(void) {
	char del[10];
	house* t = head;
	house* t_del = head->next;	//t_delΪ����ɾ���Ľ�㣬tΪ����ɾ������ǰһ�����
	system("color b0");
	system("CLS");
	printf("\n\t\t\t����Ϊ���еķ�����Ϣ\n");
	print();
	printf("\n\t\t������Ҫɾ���ķ��ݱ��:");
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
		printf("\n\t\tδ�ҵ���Ҫɾ���ķ�����Ϣ!");
	}
	else {
		t->next = t_del->next;
		printf("\n\t\t������Ϣ��ɾ����\n");
		free(t_del);
	}
	system("pause");
}