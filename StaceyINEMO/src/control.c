/*
 * control.c
 *
 *  Created on: Nov 26, 2014
 *      Author: Callen Fisher
 */

#include "control.h"

void controlAlgorithm(float* acc,float* gyro,float* angles,float*PWMval)
{
	//TODO Stacey: you need to assign a value to angles[0],angles[1],angles[2] and to PWMval
	//use setPWM(PWMval) to set the PWM value (value between 0 and 100%)
	angles[0]=5;
	angles[1]=12.1;
	angles[2]=-12.1;
	*PWMval=15;
	setPWM(PWMval);
}
