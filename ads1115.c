#include "stm32f1xx_hal.h"
#include "ads1115.h"

/************************************
  * @brief detect ads1115
  * @param I2C_InitStruct,ADS_InitStruct
  * @retval HAL_StatusTypeDefine
************************************/
HAL_StatusTypeDef IS_ADS1115_Ready(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct)
{
	uint8_t ADS_ADDR=(uint8_t)ads1115_initstruct->address|0x01;
	return HAL_I2C_IsDeviceReady(hi2c,(uint8_t)ADS_ADDR,5,0xff);
}

/************************************
  * @brief Start a Single Conversion
  * @param I2C_InitStruct,ADS_InitStruct,pResult
  * @retval HAL_StatusTypeDefine
************************************/
HAL_StatusTypeDef Start_ADS_Single(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct,
									uint8_t *result)
{
	uint8_t ADS_ADDR=(uint8_t)ads1115_initstruct->address|0x01;
	uint8_t ADS_ADDW=(uint8_t)ads1115_initstruct->address|0x00;

	uint8_t CONFIG_MSB=	ADS1115_OS_SingleConverStart
						+ads1115_initstruct->channel
						+ads1115_initstruct->ads1115_pga
						+ADS1115_MODE_SingleConver;

	uint8_t CONFIG_LSB=	ads1115_initstruct->ads1115_datarate
						+ads1115_initstruct->ads1115_comp_mode
						+ads1115_initstruct->ads1115_comp_pol
						+ads1115_initstruct->ads1115_comp_lat
						+ads1115_initstruct->ads1115_comp_que;


	uint8_t CONFIG[3]={ADS1115_Pointer_ConfigReg,CONFIG_MSB,CONFIG_LSB};
	if(HAL_I2C_Master_Transmit(hi2c,ADS_ADDW,CONFIG,3,0Xff))
		return HAL_ERROR;
	//Start single Conversion

	HAL_Delay(10);
	//Wait for Conversion

	uint8_t CMD=ADS1115_Pointer_ConverReg;
	if(HAL_I2C_Master_Transmit(hi2c,ADS_ADDW,&CMD,1,0Xff))
		return HAL_ERROR;
	if(HAL_I2C_Master_Receive(hi2c,ADS_ADDR,result,2,0xff))
		return HAL_ERROR;
	//Read Result
	return HAL_OK;
}

/************************************
  * @brief Start four Single Conversion
  * @param I2C_InitStruct,ADS_InitStruct,pResult
  * @retval HAL_StatusTypeDefine
************************************/
HAL_StatusTypeDef Start_ADS_All_Single(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct,
									uint8_t *result)
{
	uint8_t temp=ads1115_initstruct->channel;

	ads1115_initstruct->channel=SINGLE_CHANNEL_0;
	Start_ADS_Single(hi2c, ads1115_initstruct, result);

	ads1115_initstruct->channel=SINGLE_CHANNEL_1;
	Start_ADS_Single(hi2c, ads1115_initstruct, result+2);

	ads1115_initstruct->channel=SINGLE_CHANNEL_2;
	Start_ADS_Single(hi2c, ads1115_initstruct, result+4);

	ads1115_initstruct->channel=SINGLE_CHANNEL_3;
	Start_ADS_Single(hi2c, ads1115_initstruct, result+6);

	ads1115_initstruct->channel=temp;

	return HAL_OK;
}

/************************************
  * @brief Config as Continuous Mode
  * @param I2C_InitStruct,ADS_InitStruct
  * @retval HAL_StatusTypeDefine
  * NOT FINISHED!!
************************************/
HAL_StatusTypeDef Start_ADS_Continuous(I2C_HandleTypeDef *hi2c,
										ADS1115_HandelTypeDef *ads1115_initstruct)
{
//	uint8_t ADS_ADDR=(uint8_t)ads1115_initstruct->address|0x01;
	uint8_t ADS_ADDW=(uint8_t)ads1115_initstruct->address|0x00;

	uint8_t CONFIG_MSB=	ADS1115_OS_OperationalStatus
						+ads1115_initstruct->channel
						+ads1115_initstruct->ads1115_pga
						+ADS1115_MODE_ContinuConver;

	uint8_t CONFIG_LSB=	ads1115_initstruct->ads1115_datarate
						+ads1115_initstruct->ads1115_comp_mode
						+ads1115_initstruct->ads1115_comp_pol
						+ads1115_initstruct->ads1115_comp_lat
						+ads1115_initstruct->ads1115_comp_que;

	uint8_t CONFIG[3]={ADS1115_Pointer_ConfigReg,CONFIG_MSB,CONFIG_LSB};
	if(HAL_I2C_Master_Transmit(hi2c,ADS_ADDW,CONFIG,3,0Xff))
		return HAL_ERROR;
	//Config Continuous Conversion
	return HAL_OK;
}

/************************************
  * @brief Config as Continuous Mode
  * @param I2C_InitStruct,ADS_InitStruct
  * @retval HAL_StatusTypeDefine
  * NOT FINISHED!!
************************************/
HAL_StatusTypeDef Get_Result(I2C_HandleTypeDef *hi2c,
							ADS1115_HandelTypeDef *ads1115_initstruct,
							uint8_t *result)
{
	uint8_t ADS_ADDR=(uint8_t)ads1115_initstruct->address|0x01;
	uint8_t ADS_ADDW=(uint8_t)ads1115_initstruct->address|0x00;

	uint8_t CONFIG[3]={ADS1115_Pointer_ConverReg,0X00,0X00};
	if(HAL_I2C_Master_Transmit(hi2c,ADS_ADDW,CONFIG,1,0Xff))
		return HAL_ERROR;
	//Pointer Register
	if(HAL_I2C_Master_Receive(hi2c,ADS_ADDR,result,2,0xff))
		return HAL_ERROR;
	//Read Result
	return HAL_OK;
}
