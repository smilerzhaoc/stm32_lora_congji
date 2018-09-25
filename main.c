#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "string.h"
#include "ME3612.h"
#include "delay.h"
#include "led.h"
#include "main.h"
#include "lora.h"


/*************  ±¾µØ±äÁ¿ÉùÃ÷	**************/


//char Uart2_Buf[Buf2_Max];//´®¿Ú2Êı¾İ»º´æÇø
u8 First_Int = 0;


#define Buf5_Max 				240 					  //´®¿Ú5»º´æ³¤¶È
#define Buf1_Max 				240					  //´®¿Ú1»º´æ³¤¶È
#define REX_Data_Max		240						//ÓĞĞ§Êı¾İ³¤¶È
#define Send_Data_Max		1024						//·¢ËÍ×î´ó×Ö½ÚÊı
#define buff_Max		1024						//×ªÒå´¦ÀíºóÊı×é×î´ó³¤¶È



u16 USART_RX_STA;
u8 Uart5_Buf[Buf5_Max]={0};//´®¿Ú5Êı¾İ»º´æÇø
u8 Uart1_Buf[Buf1_Max]={0};//´®¿Ú1Êı¾İ»º´æÇø


/*******************************************************
*LORA 433Í¨ĞÅÏà¹Ø¶¨Òå
*
*
***********************************/
volatile uint8_t Lora_send_BUF[4];
uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN]={0};//UART5½ÓÊÕ»º³åÇø
uint8_t UART5Buf[UART5_RX_BUFFER_LEN]={0};//UART5´¦Àí»º³åÇø
uint8_t Data_Packet1[22]={0};//
uint8_t Data_Packet2[22]={0};//
uint8_t UART5RxRec;  //UART5½ÓÊÕ×Ö½ÚÊı
uint8_t UART5RxChar;//UART5½ÓÊÕ×Ö½Ú
volatile uint8_t Lora_OK=0;//½ÓÊÕÍê³É±êÖ¾
volatile uint16_t LoraTimer;    //¶ÁÈ¡¼ä¸ôÊ±¼ä
volatile u8 LoraOverTime=10;//´«¸ĞÆ÷¶ÁÈ¡³¬Ê±¿ØÖÆ
volatile u8 Lora_state=1;  
volatile u16 LoraWaittime=5000;			//µÈ´ı·şÎñÆ÷»Ø¸´Ê±¼ä
volatile u16 Lorasendtime=0;				//·¢ËÍ¼ä¸ôÊ±¼ä
volatile u8 LoraErrorTimes=0;

volatile uint8_t ReceiveBuf[6]={0};
volatile u16 RxTimeOut;


volatile u16 flag=0;







/*******************************************************************************
* º¯ÊıÃû : main 
* ÃèÊö   : Ö÷º¯Êı
* ÊäÈë   : 
* Êä³ö   : 
* ·µ»Ø   : 
* ×¢Òâ   : 
*******************************************************************************/
int main(void)
{
		
	  NBCOM_Timer=0;
		RelayTimer=0;
		RxTimeOut=0;
		delay_init();
		LED_Init();
	  LORA_Init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
		USART1_Init_Config(9600);       //NB-IOTÄ£¿é,Ä£¿é¿ª»ú¸´Î»µÈÒ²ÔÚÀïÃæ³õÊ
		USART2_Init_Config(9600);         //»·¾³²ÎÊı²âÁ¿
		USART3_Init_Config(38400);         //ÈËÁ÷Á¿»ò³µÁ÷Á¿²ÎÊı²âÁ¿
		UART4_Init_Config(9600);          //µç±íÏà¹ØÊı¾İ²âÁ¿
		UART5_Init_Config(9600);	      //433ÎŞÏßÍ¨ĞÅÄ£¿é
		Timer2_Init_Config();    
		Timer3_Init_Config();
		//ME3612Init();//Ö»Ö´ĞĞÒ»´ÎµÄ³õÊ¼»¯·ÅÔÚÕâÀï

		while(1)
		{
			
			LED_TASK(); 
			
			
			LORA_TASK();
					
ñ
		}	
}




	
