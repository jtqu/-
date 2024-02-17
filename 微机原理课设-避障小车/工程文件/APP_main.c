        #include"APP_main.h"

#define distance 40
#define distance_L 40
#define distance_R 40
#define distance_M 65
#define speed_L 20
#define speed_R 20

bit F_T=0;

unsigned char TIME2_COUNT=20;

void time2(void) interrupt 3
  {
    unsigned char ch;
    TIME2_COUNT--;
	if(TIME2_COUNT==0) 
	   {
		  TIME2_COUNT=10;
		  F_T=1;
		  TR1=1;EA=1;
        }
  }

void main()
{
 	unsigned char left = 0,right = 0,middle = 0,action0=0,action1=0;//action0��¼��һ״̬��action1��¼��ǰ״̬
	SystemInit();
	TMOD=1;
	TH1=0; TL1=0;
	TR1=1; ET1=1;
	EA=1;

    DC_Motor(LEFT_F,GOING,speed_L);  //��ǰ���
	DC_Motor(LEFT_B,GOING,speed_L);  //�����
    DC_Motor(RIGHT_F,GOING,speed_R);  //��ǰ��� 
	DC_Motor(RIGHT_B,GOING,speed_R);  //�Һ���

while(1)    
{
   if(F_T) 
      {
		 left=GetIR_Distance(9);
		 middle=GetIR_Distance(8);
	   	 right=GetIR_Distance(7);
		 Display_Char12864(1,0,"id   number",001);
         Display_Char12864(2,0,"LEFT:",left);
         Display_Char12864(3,0,"MIDDLE:",middle);
         Display_Char12864(4,0,"RIGHT:",right);
		 action1=0;
		 if (middle<distance_M) action1=3;//3����
			 else if (left<distance_L) action1=1;//1��ת
			 else if (right<distance_R) action1=2;//2��ת
		 if (action0!=action1)
		    {
			  action0=action1;
	          switch(action1)
	            {
		          case 0:   //ֱ��
		            {
					   DC_Motor(LEFT_F,GOING,speed_L);   //��ǰ���
	                   DC_Motor(LEFT_B,GOING,speed_L);   //�����
                       DC_Motor(RIGHT_F,GOING,speed_R);  //��ǰ��� 
	                   DC_Motor(RIGHT_B,GOING,speed_R);  //�Һ���
	
			         }break;
		          case 1:   //��ת
		            {
					   DC_Motor(LEFT_F,GOING,speed_L);   //��ǰ���
	                   DC_Motor(LEFT_B,GOING,speed_L);   //�����
                       DC_Motor(RIGHT_F,STOP,speed_R);  //��ǰ��� 
	                   DC_Motor(RIGHT_B,STOP,speed_R);  //�Һ���		
			         }break;
		          case 2:   //��ת
	            	{ 
					   DC_Motor(LEFT_F,STOP,speed_L);   //��ǰ���
	                   DC_Motor(LEFT_B,STOP,speed_L);   //�����
                       DC_Motor(RIGHT_F,GOING,speed_R);  //��ǰ��� 
	                   DC_Motor(RIGHT_B,GOING,speed_R);  //�Һ���				
			
	             	 }break;
				  case 3:
	            	{ 
					   DC_Motor(LEFT_F,BACK,(speed_L-5));   //��ǰ���
	                   DC_Motor(LEFT_B,BACK,(speed_L-5));   //�����
                       DC_Motor(RIGHT_F,BACK,(speed_R-5));  //��ǰ��� 
	                   DC_Motor(RIGHT_B,BACK,(speed_R-5));  //�Һ���				
			       	 }break;
                  default: break;
               }
			 }
		 F_T=0;
	  }   
   }
 }                                                                                                                                                                                               
