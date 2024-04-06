#ifndef _ADS1115_H
#define _ADS1115_H
#include "stm32f1xx_hal_def.h"


//*************ADDR Initial********************/

/************ADS1115 BASE ADDRESS*****************/
#define	ADS1115_GND							0x90	//ADDR PIN =GND
#define	ADS1115_VDD							0x92	//ADDR PIN =VDD
#define	ADS1115_SDA							0x94	//ADDR PIN =SDA
#define	ADS1115_SCL							0x96	//ADDR PIN =SCL
//ADS1115_ADDRESS_W	ADS1115_ADDRESS|0x00
//ADS1115_ADDRESS_R	ADS1115_ADDRESS|0x01


/************POINTER REGISTER*****************/
#define ADS1115_Pointer_ConverReg			0x00	//Convertion register
#define ADS1115_Pointer_ConfigReg			0x01	//Config register
#define ADS1115_Pointer_LoThreshReg			0x02	//Lo_thresh register
#define ADS1115_Pointer_HiThreshReg			0x03	//Hi_thresh register

/************CONFIG REGISTER*****************/

//Bit[15]
#define ADS1115_OS_OperationalStatus		0x00		//No Effect
#define ADS1115_OS_SingleConverStart		0x80		//Begin a single conversion
//Bits[11:9]
#define ADS1115_PGA_6144					0x00		//FS=6.144V
#define ADS1115_PGA_4096					0x02		//FS=4.096V
#define ADS1115_PGA_2048					0x04		//FS=2.048V(default)
#define ADS1115_PGA_1024					0x06		//FS=1.024V
#define ADS1115_PGA_0512					0x08		//FS=0.512V
#define ADS1115_PGA_0256					0x0A		//FS=0.256V
//Bit[8]
#define ADS1115_MODE_ContinuConver			0x00		//Continuous conversion mode
#define ADS1115_MODE_SingleConver			0x01		//Power-down single-shot mode(default)
//Bits[7:5]
#define ADS1115_DataRate_8					0x00		//Data Rate = 8
#define ADS1115_DataRate_16					0x20		//Data Rate = 16
#define ADS1115_DataRate_32					0x40		//Data Rate = 32
#define ADS1115_DataRate_64					0x60		//Data Rate = 64
#define ADS1115_DataRate_128				0x80		//Data Rate = 128(default)
#define ADS1115_DataRate_250				0xA0		//Data Rate = 250
#define ADS1115_DataRate_475				0xC0		//Data Rate = 475
#define ADS1115_DataRate_860				0xE0		//Data Rate = 860
//Bit[4]
#define ADS1115_COMP_MODE_0					0x00		//Traditional comparator with hysteresis
#define ADS1115_COMP_MODE_1					0x10		//Window comparator
//Bit[3]
#define ADS1115_COMP_POL_0					0x00		//Active low, generate a high pulse when conversion finished
#define ADS1115_COMP_POL_1					0x08		//Active high, generate a high pulse when conversion finished
//Bit[2]
#define ADS1115_COMP_LAT_0					0x00		//Non-latching comparator
#define ADS1115_COMP_LAT_1					0x04		//Latching comparator
//Bits[1:0]
#define ADS1115_COMP_QUE_0					0x00		//Assert after one conversion
#define ADS1115_COMP_QUE_1					0x01		//Assert after two conversion
#define ADS1115_COMP_QUE_2					0x02		//Assert after four conversion
#define ADS1115_COMP_QUE_3					0x03		//Disable Comparator

typedef enum
{
	ADS1115_ADDRESS_GND=0x90,
	ADS1115_ADDRESS_VDD=0x92,
	ADS1115_ADDRESS_SDA=0x94,
	ADS1115_ADDRESS_SCL=0x96
}ADS1115_ADDRESS;

typedef enum
{
	DIFF_CHANNEL_01=0X00,
	DIFF_CHANNEL_03=0X10,
	DIFF_CHANNEL_13=0X20,
	DIFF_CHANNEL_23=0X30,
	SINGLE_CHANNEL_0=0x40,
	SINGLE_CHANNEL_1=0x50,
	SINGLE_CHANNEL_2=0x60,
	SINGLE_CHANNEL_3=0x70
}ADS1115_CHANNEL;

typedef struct
{
	ADS1115_ADDRESS address;
	ADS1115_CHANNEL channel;
	uint8_t ads1115_pga;
	uint8_t ads1115_datarate;
	uint8_t ads1115_comp_mode;
	uint8_t ads1115_comp_pol;
	uint8_t ads1115_comp_lat;
	uint8_t ads1115_comp_que;

	uint8_t hi_thresh_msb;
	uint8_t hi_thresh_lsb;
	uint8_t lo_thresh_msb;
	uint8_t lo_thresh_lsb;
}ADS1115_HandelTypeDef;


/***********Detect ADS1115**********/
HAL_StatusTypeDef IS_ADS1115_Ready(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct);

/***********Start a Single Shot and Get one Result**********/
HAL_StatusTypeDef Start_ADS_Single(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct,
									uint8_t *result);

HAL_StatusTypeDef Start_ADS_All_Single(I2C_HandleTypeDef *hi2c,
									ADS1115_HandelTypeDef *ads1115_initstruct,
									uint8_t *result);

/***********Start Continuous Shot**********/
/*************NOT FINISHED!!***************/
HAL_StatusTypeDef Start_ADS_Continuous(I2C_HandleTypeDef *hi2c,ADS1115_HandelTypeDef *ads1115_initstruct);
HAL_StatusTypeDef Get_Result(I2C_HandleTypeDef *hi2c,ADS1115_HandelTypeDef *ads1115_initstruct,uint8_t *result);

#endif
