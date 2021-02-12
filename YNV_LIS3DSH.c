/*
 * YNV_LIS3DSH.c
 *
 *  Created on: Jan 12, 2021
 *      Author: leoch
 */

#include "YNV_LIS3DSH.h"

LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *hspi, uint8_t reg_addr, uint8_t *dataW)
{
	reg_addr &= 0x7F;
	uint8_t tab[2] = {reg_addr,*dataW};
	CS_LOW;
	if(HAL_SPI_Transmit(hspi, tab, 2, 10) == HAL_OK)
	{
		CS_HIGH;
		return LIS3DSH_OK;
	}
	CS_HIGH;
	return LIS3DSH_ERROR;
}

LIS3DSH_Status_t LIS3DSH_Read_reg(SPI_HandleTypeDef *hspi, uint8_t reg_addr, uint8_t *dataR, uint8_t size)
{
	reg_addr |= 0x80;

	CS_LOW;
	if (HAL_SPI_Transmit(hspi, &reg_addr, 1, 10) == HAL_OK)
	{
		if (HAL_SPI_Receive(hspi, dataR, size, 10) == HAL_OK)
		{
			CS_HIGH;
			return LIS3DSH_OK;
		}
	}
	CS_HIGH;
	return LIS3DSH_ERROR;
}

LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *hspi, LIS3DSH_init_t *poseInitDef)
{
	uint8_t spiData[2] = {0x00,0x00} ;
	uint8_t spiCheckData[2] = { 0x00, 0x00 };

	spiData[0] |= (poseInitDef->axisSelect | (LIS3DSH_X_ENABLE | LIS3DSH_Y_ENABLE | LIS3DSH_50_ODR));
	spiData[1] |= (poseInitDef->scale | LIS3DSH_SCALE_4G);

	if(LIS3DSH_Write_reg(hspi, LIS3DSH_CR_REG4, &spiData[0])== LIS3DSH_OK)
	{
		if (LIS3DSH_Read_reg(hspi, LIS3DSH_CR_REG4, &spiCheckData[0], 2) == LIS3DSH_OK)
		{
			if (spiCheckData[0] == spiData[0])
			{
				if (LIS3DSH_Write_reg(hspi, LIS3DSH_CR_REG5, &spiData[1]) == LIS3DSH_OK)
				{
					if (LIS3DSH_Read_reg(hspi, LIS3DSH_CR_REG5, &spiCheckData[1], 2) == LIS3DSH_OK)
					{
						if (spiCheckData[1] == spiData[1])
						{
							return LIS3DSH_OK;
						}
					}
				}
			}
		}
	}
	return LIS3DSH_ERROR;
}

LIS3DSH_Status_t LIS3DSH_Get_pos(SPI_HandleTypeDef *hspi, uint16_t *dataXY)
{
	uint8_t dataRaw_L ;
	uint8_t dataRaw_H ;
	if (LIS3DSH_Read_reg(hspi, LIS3DSH_X_DATA_L, &dataRaw_L, 1) == LIS3DSH_OK)
	{
		if (LIS3DSH_Read_reg(hspi, LIS3DSH_X_DATA_H, &dataRaw_H, 1) == LIS3DSH_OK)
		{
			dataXY[0] = (dataRaw_H << 8 | dataRaw_L);
			if (LIS3DSH_Read_reg(hspi, LIS3DSH_Y_DATA_L, &dataRaw_L, 1) == LIS3DSH_OK)
			{
				if (LIS3DSH_Read_reg(hspi, LIS3DSH_Y_DATA_H, &dataRaw_H, 1) == LIS3DSH_OK)
				{
					dataXY[1] = (dataRaw_H << 8 | dataRaw_L);
					return LIS3DSH_OK;
				}

			}
		}
	}
	return LIS3DSH_ERROR;
}











