#include "lora.h"
#include "delay.h"
#include "main.h"
#include "usart.h"

#define LoraStartByte 17

extern volatile uint8_t Lora_send_BUF[4];
extern uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN];//UART5���ջ�����
extern uint8_t UART5Buf[UART5_RX_BUFFER_LEN];//UART5��������
extern uint8_t Data_Packet1[22];//
extern uint8_t Data_Packet2[22];//
extern uint8_t UART5RxRec;  //UART5�����ֽ���
extern uint8_t UART5RxChar;//UART5�����ֽ�
extern volatile uint8_t Lora_OK;//������ɱ�־
extern volatile uint16_t LoraTimer;    //��ȡ���ʱ��, Ŀǰ��200ms��ȡһ��
extern volatile u8 LoraOverTime;//��������ȡ��ʱ����

extern volatile u16 LoraWaittime;			//�ȴ��������ظ�ʱ��
extern volatile u16 Lorasendtime;

extern volatile uint8_t ReceiveBuf[6];
extern uint8_t Data_Send_Packet[PacketLen];

extern volatile u16 flag;

void LORA_Init(void)
{
 
		 GPIO_InitTypeDef  GPIO_InitStructure;
			
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE );  //ʹ��PB�˿�ʱ��
	
			//M1
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //MD1  PB8
			GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			//M0
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //MD0  PB9
			GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			//MD1=0,MD0=0;
			GPIO_ResetBits(GPIOB, GPIO_Pin_11);
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
}

void LORA_TASK()
{
		u16 ThisCheckSum;
		uint16_t cChecksum;
		u8 Lora_send_BUF[4]={0xaa,0x01,0x12,0x34};
		Data_Packet2[0]=UART5RxBuf[0];

			
			cChecksum = (UART5RxBuf[0]+UART5RxBuf[1]+UART5RxBuf[2]+UART5RxBuf[3]);	
			if(Lora_OK==1)
			{
				if(cChecksum == 0xff)     
				{
					
					if(LoraTimer==20)	//200ms��ʱ�ѵ�  ���Ͷ�ȡָ��
					{
							UART5RxRec = 0;
							LoraTimer=0;
							//��������
							UART5_LenSendString(Lora_send_BUF,4);//���Ͷ�ȡ���������������
						Data_Packet2[0]=UART5RxBuf[0];
						Data_Packet2[1]=UART5RxBuf[1];
					}	
			
					Lora_OK=0;			
				}
		 }
			
}

