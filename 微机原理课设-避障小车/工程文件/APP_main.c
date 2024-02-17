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
 	unsigned char left = 0,right = 0,middle = 0,action0=0,action1=0;//action0记录上一状态，action1记录当前状态
	SystemInit();
	TMOD=1;
	TH1=0; TL1=0;
	TR1=1; ET1=1;
	EA=1;

    DC_Motor(LEFT_F,GOING,speed_L);  //左前电机
	DC_Motor(LEFT_B,GOING,speed_L);  //左后电机
    DC_Motor(RIGHT_F,GOING,speed_R);  //右前电机 
	DC_Motor(RIGHT_B,GOING,speed_R);  //右后电机

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
		 if (middle<distance_M) action1=3;//3后退
			 else if (left<distance_L) action1=1;//1右转
			 else if (right<distance_R) action1=2;//2左转
		 if (action0!=action1)
		    {
			  action0=action1;
	          switch(action1)
	            {
		          case 0:   //直走
		            {
					   DC_Motor(LEFT_F,GOING,speed_L);   //左前电机
	                   DC_Motor(LEFT_B,GOING,speed_L);   //左后电机
                       DC_Motor(RIGHT_F,GOING,speed_R);  //右前电机 
	                   DC_Motor(RIGHT_B,GOING,speed_R);  //右后电机
	
			         }break;
		          case 1:   //右转
		            {
					   DC_Motor(LEFT_F,GOING,speed_L);   //左前电机
	                   DC_Motor(LEFT_B,GOING,speed_L);   //左后电机
                       DC_Motor(RIGHT_F,STOP,speed_R);  //右前电机 
	                   DC_Motor(RIGHT_B,STOP,speed_R);  //右后电机		
			         }break;
		          case 2:   //左转
	            	{ 
					   DC_Motor(LEFT_F,STOP,speed_L);   //左前电机
	                   DC_Motor(LEFT_B,STOP,speed_L);   //左后电机
                       DC_Motor(RIGHT_F,GOING,speed_R);  //右前电机 
	                   DC_Motor(RIGHT_B,GOING,speed_R);  //右后电机				
			
	             	 }break;
				  case 3:
	            	{ 
					   DC_Motor(LEFT_F,BACK,(speed_L-5));   //左前电机
	                   DC_Motor(LEFT_B,BACK,(speed_L-5));   //左后电机
                       DC_Motor(RIGHT_F,BACK,(speed_R-5));  //右前电机 
	                   DC_Motor(RIGHT_B,BACK,(speed_R-5));  //右后电机				
			       	 }break;
                  default: break;
               }
			 }
		 F_T=0;
	  }   
   }
 }                                                                                                                                                                                               
