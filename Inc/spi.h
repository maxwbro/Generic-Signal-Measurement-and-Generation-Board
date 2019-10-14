/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

 uint8_t IC_GD_Write_Reg_1(uint8_t reg, uint8_t value);  // write chip1's register
 uint8_t IC_GD_Read_Reg_1(uint8_t reg);                  // read chip1's register
 uint8_t IC_GD_Write_Reg_2(uint8_t reg, uint8_t value);  // write chip2's register
 uint8_t IC_GD_Read_Reg_2(uint8_t reg);                  // read chip2's register
 uint8_t* Process_Data_1p2p_bc(uint8_t data_1_1p, uint8_t data_1_2p, uint8_t data_2_1p, uint8_t data_2_2p ); // process data in broadcast mode

 /*different situation 1p-2p data type(in bytes) */

 uint8_t* Process_Data_1p2p_1to1(uint8_t opcode, uint8_t data_1p, uint8_t data_2p);   // 1p-2p data type 1-1
 uint8_t* Process_Data_1p2p_1to2(uint8_t opcode, uint8_t data_1p, uint16_t data_2p);  // 1p-2p data type 1-2
 uint8_t* Process_Data_1p2p_1to4(uint8_t opcode, uint8_t data_1p, uint32_t data_2p);  // 1p-2p data type 1-4
 uint8_t* Process_Data_1p2p_2to1(uint8_t opcode, uint16_t data_1p, uint8_t data_2p);  // 1p-2p data type 2-1
 uint8_t* Process_Data_1p2p_2to2(uint8_t opcode, uint16_t data_1p, uint16_t data_2p); // 1p-2p data type 2-2
 uint8_t* Process_Data_1p2p_2to4(uint8_t opcode, uint16_t data_1p, uint32_t data_2p); // 1p-2p data type 2-4
 uint8_t* Process_Data_1p2p_4to1(uint8_t opcode, uint32_t data_1p, uint8_t data_2p);  // 1p-2p data type 4-1
 uint8_t* Process_Data_1p2p_4to2(uint8_t opcode, uint32_t data_1p, uint16_t data_2p); // 1p-2p data type 4-2
 uint8_t* Process_Data_1p2p_4to4(uint8_t opcode, uint32_t data_1p, uint32_t data_2p); // 1p-2p data type 4-4

 /* register initialing function */

 void IC_GD_Reg_Init(uint8_t reg_address[49], uint8_t reg_val1[49], uint8_t reg_val2[49]);

 /* error handler function */

 void IC_GD_read_Error(void);
 void IC_GD_write_Error(void);

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */

#define BUFFERSIZE                   49


/* opcodes write and read the register */

#define read_IC_GD_CMD_1             0xA0
#define read_IC_GD_CMD_2             0xA1
#define write_IC_GD_CMD_1            0xB0
#define write_IC_GD_CMD_2            0xB1

/* opcodes for processing data */

#define process_IC_GD_1p2p           0x2F
#define process_IC_GD_1p2p_1         0x20  // chip1 process data 1p&2p in single mode
#define process_IC_GD_1p2p_2         0x21  // chip2 process data 1p&2p in single mode

/* time out */

#define time_out                     0x00

/*ENABLE iC-GD*/

#define IC_GD_Enable()               HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);  // enable iC-GD
#define IC_GD_Disable()              HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);    // disable iC-GD

/* select rs232/CAN */



/* I/O modes for IC_GD */
/*       S_P           */
/*      DI_P           */

#define DI_VI                        0x02   // p: 2-bytes
#define DI_CI                        0x04   // p: 2-bytes
#define DI_VO                        0x03   // p: 2-bytes
#define DI_TM                        0x07   // p: 2-bytes

/*      DO_P           */

#define DO_VI                        0x12   // p: 2-bytes
#define DO_CO                        0x14   // p: 2-bytes
#define DO_VO                        0x13   // p: 2-bytes
#define DO_TM                        0x17   // p: 2-bytes

/*      VI_P           */

#define VI_DI                        0x20   // p: 1-byte
#define VI_DO                        0x21   // p: 1-byte
#define VI_CO                        0x25   // p: 2-bytes
#define VI_CNT                       0x26   // p: 4-bytes

/*      CI_P           */

#define CI_DI                        0x40   // p: 1-byte
#define CI_DO                        0x41   // p: 1-byte
#define CI_CO                        0x45   // p: 2-bytes
#define CI_CNT                       0x46   // p: 4-bytes

/*      VO_P           */

#define VO_DI                        0x30   // p: 1-byte
#define VO_DO                        0x31   // p: 1-byte
#define VO_CO                        0x35   // p: 2-bytes
#define VO_CNT                       0x36   // p: 4-bytes

/*      CO_P           */

#define CO_VI                        0x52   // p: 2-bytes
#define CO_CI                        0x54   // p: 2-bytes
#define CO_VO                        0x53
#define CO_TM                        0x57

/*      OFF_P           */

#define OFF_DI                       0x70   // p: 1-byte
#define OFF_DO                       0x71
#define OFF_VI                       0x72   // p: 2-bytes
#define OFF_VO                       0x73
#define OFF_CI                       0x74   // p: 2-bytes
#define OFF_CO                       0x75
#define OFF_CNT                      0x76   // p: 4-bytes
#define OFF_TM                       0x77

/* USER CODE END Private defines */

void MX_SPI1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
