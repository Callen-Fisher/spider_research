/*
 * control.h
 *
 *  Created on: Nov 26, 2014
 *      Author: Callen Fisher
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <stddef.h>
#include "stm32f10x.h"

void controlAlgorithm(float* acc,float* gyro,float* angles,float*PWMval);

#endif /* CONTROL_H_ */
