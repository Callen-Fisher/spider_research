/*
 * gyro.h
 *
 *  Created on: Sep 13, 2014
 *      Author: Callen Fisher
 */

#ifndef GYRO_H_
#define GYRO_H_

#include "stm32f10x.h"
#include <stddef.h>

void setUpGyro(void);
void initSPIgyro(void);
void spiGyroRegisterSetup(void);
uint8_t writeSPIgyro(uint8_t regAdr, uint8_t data);
void getGyro(u8* data,float* out );
void getTemp(u8*temp);
s16 twosCompToDec16(u16 val);
s8 twosCompToDec8(u8 val);

#endif /* GYRO_H_ */
