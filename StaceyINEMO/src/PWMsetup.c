/*
 * PWMsetup.c
 *
 *  Created on: Nov 26, 2014
 *      Author: Callen Fisher
 */

#include "PWMsetup.h"

void pwm()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//tim3 ch1 //PA6
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

	TIM_TimeBaseStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=20000;//TODO SET THE FREQUENCY
	TIM_TimeBaseStruct.TIM_Prescaler=0;
	TIM_TimeBaseStruct.TIM_RepetitionCounter=0x0000;

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	TIM_OCInitTypeDef OC;

	OC.TIM_OCMode=TIM_OCMode_PWM1;
	OC.TIM_OutputState=TIM_OutputState_Enable;
	OC.TIM_Pulse=10000;
	OC.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&OC);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3,DISABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_SetCompare1(TIM3,20000);//inversed//set compare sets the duty (val between 0 and 40 000 where 40000 is 0% and 0 is 100%
}


void setPWM(float* valPercentage)
{
	//40 000 is 0% and 0 is 100%
	float valPercentage2=100.0-*valPercentage;

	valPercentage2=valPercentage2/100.0*20000;
	uint16_t v=(uint16_t)valPercentage2;
	TIM_SetCompare1(TIM3,v);
}
