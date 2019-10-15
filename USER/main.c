#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

 
/************************************************
 ALIENTEKս��STM32������ʵ��10
 ���벶��ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //��ʾ�¶�
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
u32 Distance;                               //���������
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;  //��ʱ�͵��εȱ���
float Acceleration_Z;                       //Z����ٶȼ�
float Balance_Kp=2200,Balance_Kd=2,Velocity_Kp=80,Velocity_Ki=0.4;//PID����
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash������� 

 int main(void)
 {		
 	u32 temp=0; 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� 
	Encoder_Init_TIM2();            //=====�������ӿ�
    Encoder_Init_TIM4();            //=====��ʼ��������2
	Adc_Init();                     //=====adc��ʼ��
	OLED_Init();
	IIC_Init();                     //=====IIC��ʼ��
    MPU6050_initialize();           //=====MPU6050��ʼ��	
    DMP_Init();                     //=====��ʼ��DMP 
	MiniBalance_EXTI_Init();        //=====MPU6050 5ms��ʱ�жϳ�ʼ��
	 
// 	TIM3_PWM_Init(899,0); 		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
// 	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
	 
	OLED_P6x8Str(72,7,"Maker:Tyz",0);
   	while(1)
	{
//		printf("Encoder_Left:%x  Encoder_Right:%x",Encoder_Left,Encoder_Right);
//		PWMA=3000;
//		OLED_P8x16Str(0,0,"FM:",0);
		if(Flag_Show==0)          //ʹ��MiniBalance APP��OLED��ʾ��
		{
			oled_show();          //===��ʾ����
		}
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼��ʱ	
		
// 		delay_ms(10);
//		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

//		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
//		 		 
// 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
//		{
//			temp=TIM5CH1_CAPTURE_STA&0X3F;
//			temp*=65536;//���ʱ���ܺ�
//			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
//			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
//			TIM5CH1_CAPTURE_STA=0;//������һ�β���
//		}
	}
 }

