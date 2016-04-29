
#include <stddef.h>
#include "stm32f10x.h"
#include "AccMag.h"
#include "gyro.h"
#include "XBEE.h"
#include "serial_terminal.h"
#include "CRC.h"
#include "controlLoopTimer.h"
#include "control.h"
#include "PWMsetup.h"
uint16_t recVal;
float acc[3];
float gyro[3];
float PWMval;
float angles[3];

uint8_t acc8[6];
uint8_t gyro8[6];
uint8_t angles8[12];
uint8_t PWMval8[4];

void convertAnglesToBytes(void);
void setUpLED(void);
void turnOnLED(void);
void turnOffLED(void);

int main(void)
{
  serialTerminal_Init();
  setUpEcompass();
  setUpGyro();
  setUpXbee();
  setUpLoopTimer();
  pwm();
  setUpLED();
  int p=0;

  while (1)
  {
	  getAcc(acc8,acc);//send the floats as well
	  getGyro(gyro8,gyro);

	  //control must get the angles
	  controlAlgorithm(acc,gyro,angles,&PWMval);

	  convertAnglesToBytes();
	  for(p=0;p<sizeof(TxBuff);p++)
	  {
	  	TxBuff[p]=0;
	  }
	  DMA_Cmd(DMA1_Channel7, DISABLE);
	  DMA_SetCurrDataCounter(DMA1_Channel7,sizeof(TxBuff));
	  serialTerminal_packetize(gyro8,acc8,angles8,PWMval8,sizeof(gyro8),sizeof(acc8),sizeof(angles8),sizeof(PWMval8));

	  DMA_Cmd(DMA1_Channel7, ENABLE);
	  USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	  USART_Cmd(USART2, ENABLE);


	  wait();
  }
}
void convertAnglesToBytes()
{
	union
	{
		 char temp_char[12];
		 float temp_int_buffer[3];
	}buffer_to_char_union1;
	buffer_to_char_union1.temp_int_buffer[0]=angles[0];
	buffer_to_char_union1.temp_int_buffer[1]=angles[1];
	buffer_to_char_union1.temp_int_buffer[2]=angles[2];
	int i;
	for(i=0;i<12;i++)
	{
		angles8[i]=buffer_to_char_union1.temp_char[i];
	}

	union
	{
		 char temp_char[4];
		 float temp_int_buffer;
	}buffer_to_char_union2;
	buffer_to_char_union2.temp_int_buffer=PWMval;
	for(i=0;i<4;i++)
	{
		PWMval8[i]=buffer_to_char_union2.temp_char[i];
	}
}
void setUpLED()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//tim3 ch1 //PA6
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	turnOnLED();
}
void turnOnLED()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}
void turnOffLED()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
