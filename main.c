#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "string.h"
#include "ME3612.h"
#include "delay.h"
#include "led.h"
#include "main.h"
#include "lora.h"


/*************  ���ر�������	**************/


//char Uart2_Buf[Buf2_Max];//����2���ݻ�����
u8 First_Int = 0;


#define Buf5_Max 				240 					  //����5���泤��
#define Buf1_Max 				240					  //����1���泤��
#define REX_Data_Max		240						//��Ч���ݳ���
#define Send_Data_Max		1024						//��������ֽ���
#define buff_Max		1024						//ת�崦���������󳤶�



u16 USART_RX_STA;
u8 Uart5_Buf[Buf5_Max]={0};//����5���ݻ�����
u8 Uart1_Buf[Buf1_Max]={0};//����1���ݻ�����


/*******************************************************
*LORA 433ͨ����ض���
*
*
***********************************/
volatile uint8_t Lora_send_BUF[4];
uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN]={0};//UART5���ջ�����
uint8_t UART5Buf[UART5_RX_BUFFER_LEN]={0};//UART5��������
uint8_t Data_Packet1[22]={0};//
uint8_t Data_Packet2[22]={0};//
uint8_t UART5RxRec;  //UART5�����ֽ���
uint8_t UART5RxChar;//UART5�����ֽ�
volatile uint8_t Lora_OK=0;//������ɱ�־
volatile uint16_t LoraTimer;    //��ȡ���ʱ��
volatile u8 LoraOverTime=10;//��������ȡ��ʱ����
volatile u8 Lora_state=1;  
volatile u16 LoraWaittime=5000;			//�ȴ��������ظ�ʱ��
volatile u16 Lorasendtime=0;				//���ͼ��ʱ��
volatile u8 LoraErrorTimes=0;

volatile uint8_t ReceiveBuf[6]={0};
volatile u16 RxTimeOut;


volatile u16 flag=0;







/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
int main(void)
{
		
	  NBCOM_Timer=0;
		RelayTimer=0;
		RxTimeOut=0;
		delay_init();
		LED_Init();
	  LORA_Init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
		USART1_Init_Config(9600);       //NB-IOTģ��,ģ�鿪����λ��Ҳ��������
		USART2_Init_Config(9600);         //������������
		USART3_Init_Config(38400);         //��������������������
		UART4_Init_Config(9600);          //���������ݲ���
		UART5_Init_Config(9600);	      //433����ͨ��ģ��
		Timer2_Init_Config();    
		Timer3_Init_Config();
		//ME3612Init();//ִֻ��һ�εĳ�ʼ����������

		while(1)
		{
			
			LED_TASK(); 
			
			
			LORA_TASK();
					
�
		}	
}




	
