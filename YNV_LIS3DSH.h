/*
 * YNV_LIS3DSH.h
 *
 *  Created on: 11 janv. 2021
 *      Author: leoch
 */

#ifndef INC_YNV_LIS3DSH_H_
#define INC_YNV_LIS3DSH_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

/* register Address define */

#define LIS3DSH_CR_REG4			0x20
#define LIS3DSH_CR_REG3			0x23
#define LIS3DSH_CR_REG5			0x24
#define LIS3DSH_STATUS			0x27
#define LIS3DSH_X_DATA_L		0x28
#define LIS3DSH_X_DATA_H		0x29
#define LIS3DSH_Y_DATA_L		0x2A
#define LIS3DSH_Y_DATA_H		0x2B
#define LIS3DSH_WHO_AM_I 		0x0F

#define CS_LOW 				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3,GPIO_PIN_RESET)
#define CS_HIGH             HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3,GPIO_PIN_SET)

/* Configuration parameters define */

//50Hz
#define LIS3DSH_X_ENABLE			((uint8_t)0x01)
#define LIS3DSH_Y_ENABLE			((uint8_t)0x02)
#define LIS3DSH_Z_ENABLE			((uint8_t)0x04)
#define LIS3DSH_XYZ_ENABLE			((uint8_t)0x07)

#define LIS3DSH_12_5_ODR			((uint8_t)0x30)
#define LIS3DSH_25_ODR				((uint8_t)0x40)
#define LIS3DSH_50_ODR				((uint8_t)0x50)
#define LIS3DSH_100_ODR				((uint8_t)0x60)
#define LIS3DSH_400_ODR				((uint8_t)0x70)
#define LIS3DSH_1600_ODR			((uint8_t)0x90)

#define	LIS3DSH_INT_ENABLE			((uint8_t)xFD)
/*Default: Interrupts disable*/

#define LIS3DSH_SCALE_2G			((uint8_t)0x00)
#define LIS3DSH_SCALE_4G			((uint8_t)0x08)
#define LIS3DSH_SCALE_6G			((uint8_t)0x10)
#define LIS3DSH_SCALE_8G			((uint8_t)0x18)
#define LIS3DSH_SCALE_16G			((uint8_t)0x20)

#define LIS3DSH_SPI_MODE_3			((uint8_t)0x01)
#define LIS3DSH_SPI_MODE_4			((uint8_t)0x00)

/* Init struct */

typedef struct
{
	uint8_t axisSelect;
	uint8_t freqSelect;
	uint8_t interruption;
	uint8_t scale;
	uint8_t SPIMode;
}LIS3DSH_init_t;

typedef enum
{
	LIS3DSH_OK,
	LIS3DSH_ERROR
}LIS3DSH_Status_t;

/*Write function*/

LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *hspi,
					uint8_t reg_addr,
					uint8_t *dataW);

/* Read function */

LIS3DSH_Status_t LIS3DSH_Read_reg(SPI_HandleTypeDef *hspi,
					uint8_t reg_addr,
					uint8_t *dataW,
					uint8_t size);

/* Init function */

LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *hspi,
					LIS3DSH_init_t *poseInitDef);

/* Get position */

LIS3DSH_Status_t LIS3DSH_Get_pos(SPI_HandleTypeDef *hspi,
					uint16_t dataXY[2]);









#endif /* INC_YNV_LIS3DSH_H_ */
