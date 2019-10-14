/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* iC-GD register address FOR EACH CHIPS */

uint8_t reg_address_1[BUFFERSIZE] ={
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1B,
		0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x39, 0x3A, 0x3B, 0x3D,
		0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,

};

uint8_t reg_val_1[BUFFERSIZE] ={
		DI_VO, 0x03, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70,
		DI_VO, 0x03, 0x07, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xA6, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

uint8_t reg_val_2[BUFFERSIZE] ={
		VI_DO, 0x03, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70,
		VI_CO, 0x03, 0x07, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xA6, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

/*Input Data Types*/


/* Processing Data Types chip1 */

uint8_t data1_1p_1;
uint16_t data1_1p_2;
uint32_t data1_1p_4;
uint8_t data1_2p_1;
uint16_t data1_2p_2;
uint32_t data1_2p_4;

/* Processing Data Types chip2 */

uint8_t data2_1p_1;
uint16_t data2_1p_2;
uint32_t data2_1p_4;
uint8_t data2_2p_1;
uint16_t data2_2p_2;
uint32_t data2_2p_4;


/* Middle Pointer */

uint8_t* p1;
uint8_t* p2;

/* I/O status */

uint8_t IOSEL1_1;
uint8_t IOSEL1_2;
uint8_t IOSEL2_1;
uint8_t IOSEL2_2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* Initialize IC-GD Register */

  IC_GD_Reg_Init(reg_address_1, reg_val_1, reg_val_2);
  mode_setting();  //manually setting the mode by dip-swithes

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

		IOSEL1_1 = IC_GD_Read_Reg_1(0x00);
		IOSEL1_2 = IC_GD_Read_Reg_1(0x10);

		IOSEL2_1 = IC_GD_Read_Reg_2(0x00);
		IOSEL2_2 = IC_GD_Read_Reg_2(0x10);

	   /*  chip1  */


	   if((IOSEL1_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL1_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 1to1
	   {
		   uint8_t data1_1p[1];
		   uint8_t data1_2p[1];
		   p1 = Process_Data_1p2p_1to1(process_IC_GD_1p2p_1,data1_1p_1, data1_2p_1);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_2p[0] = p1[2];  // 2p data input

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
       {
		   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
		   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
		   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
		   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
       }
	   else
	   {
		   HAL_UART_Transmit(&huart1, data1_1p, 1, time_out);
		   HAL_UART_Transmit(&huart1, data1_2p, 1, time_out);
		   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
		   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
	   }

	   }
	   else if((IOSEL1_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL1_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 1to2
	   {
		   uint8_t data1_1p[1];
		   uint8_t data1_2p[2];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_1, data1_2p_2);
		   data1_1p[0] = p1[1];  // 1p data input

		   data1_2p[0] = p1[2];  // 2p data input
		   data1_2p[1] = p1[3];

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }
	   else if((IOSEL1_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL1_2==(0x26||0x36||0x46||0x76)))  // chip1 1to4
	   {
		   uint8_t data1_1p[1];
		   uint8_t data1_2p[4];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_1, data1_2p_4);
		   data1_1p[0] = p1[1];  // 1p data input

		   data1_2p[0] = p1[2];  // 2p data input
		   data1_2p[1] = p1[3];
		   data1_2p[2] = p1[4];
		   data1_2p[3] = p1[5];

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }
	   else if((IOSEL1_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL1_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 2to1
	   {
		   uint8_t data1_1p[2];
		   uint8_t data1_2p[1];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_2, data1_2p_1);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1]= p1[2];

		   data1_2p[0] = p1[3];// 2p data input

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }
	   else if((IOSEL1_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL1_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 2to2
	   {
		   uint8_t data1_1p[2];
		   uint8_t data1_2p[2];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_2, data1_2p_2);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1]= p1[2];

		   data1_2p[0] = p1[3];
		   data1_2p[1] = p1[4];// 2p data input

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }
	   else if((IOSEL1_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL1_2==(0x26||0x36||0x46||0x76))) // chip1 2to4
	   {
		   uint8_t data1_1p[2];
		   uint8_t data1_2p[4];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_2, data1_2p_4);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1]= p1[2];

		   data1_2p[0] = p1[3];
		   data1_2p[1] = p1[4];// 2p data input
		   data1_2p[2] = p1[5];
		   data1_2p[3] = p1[6];

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL1_1==(0x26||0x36||0x46||0x76))&&(IOSEL1_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 4to1
	   {
		   uint8_t data1_1p[4];
		   uint8_t data1_2p[1];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_4, data1_2p_1);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1] = p1[2];
		   data1_1p[2] = p1[3];
		   data1_1p[3] = p1[4];

		   data1_2p[0] = p1[5]; // 2p data input

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }


	   }
	   else if((IOSEL1_1==(0x26||0x36||0x46||0x76))&&(IOSEL1_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 4to2
	   {
		   uint8_t data1_1p[4];
		   uint8_t data1_2p[2];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_4, data1_2p_2);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1] = p1[2];
		   data1_1p[2] = p1[3];
		   data1_1p[3] = p1[4];

		   data1_2p[0] = p1[5]; // 2p data input
		   data1_2p[1] = p1[6];

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }
	   else if((IOSEL1_1==(0x26||0x36||0x46||0x76))&&(IOSEL1_2==(0x26||0x36||0x46||0x76)))  // chip1 4to4
	   {
		   uint8_t data1_1p[4];
		   uint8_t data1_2p[4];
		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_1,data1_1p_4, data1_2p_4);
		   data1_1p[0] = p1[1];  // 1p data input
		   data1_1p[1] = p1[2];
		   data1_1p[2] = p1[3];
		   data1_1p[3] = p1[4];

		   data1_2p[0] = p1[5]; // 2p data input
		   data1_2p[1] = p1[6];
		   data1_2p[2] = p1[7];
		   data1_2p[3] = p1[8];

		   uint8_t data1_1s[2];
		   uint8_t data1_2s[2];

		   data1_1s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_1s[1] = IC_GD_Read_Reg_1(0x35);
		   data1_2s[0] = IC_GD_Read_Reg_1(0x34);   // 1s data input
		   data1_2s[1] = IC_GD_Read_Reg_1(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data1_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data1_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data1_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data1_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data1_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data1_2s, 2, time_out);
		   }

	   }


	/*  chip2  */

	   if((IOSEL2_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL2_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 1to1
	   {
		   uint8_t data2_1p[1];
		   uint8_t data2_2p[1];
		   p2 = Process_Data_1p2p_1to1(process_IC_GD_1p2p_2,data2_1p_1, data2_2p_1);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_2p[0] = p2[2];  // 2p data input

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }

	   else if((IOSEL2_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL2_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 1to2
	   {
		   uint8_t data2_1p[1];
		   uint8_t data2_2p[2];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_1, data2_2p_2);
		   data2_1p[0] = p2[1];  // 1p data input

		   data2_2p[0] = p2[2];  // 2p data input
		   data2_2p[1] = p2[3];

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71))&&(IOSEL2_2==(0x26||0x36||0x46||0x76)))  // chip1 1to4
	   {
		   uint8_t data2_1p[1];
		   uint8_t data2_2p[4];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_1, data2_2p_4);
		   data2_1p[0] = p2[1];  // 1p data input

		   data2_2p[0] = p2[2];  // 2p data input
		   data2_2p[1] = p2[3];
		   data2_2p[2] = p2[4];
		   data2_2p[3] = p2[5];

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL2_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 2to1
	   {
		   uint8_t data2_1p[2];
		   uint8_t data2_2p[1];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_2, data2_2p_1);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_1p[1]= p2[2];

		   data2_2p[0] = p2[3];// 2p data input

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL2_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 2to2
	   {
		   uint8_t data2_1p[2];
		   uint8_t data2_2p[2];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_2, data2_2p_2);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_1p[1]= p2[2];

		   data2_2p[0] = p2[3];
		   data2_2p[1] = p2[4];// 2p data input

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75))&&(IOSEL2_2==(0x26||0x36||0x46||0x76))) // chip1 2to4
	   {
		   uint8_t data2_1p[2];
		   uint8_t data2_2p[4];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_2, data2_2p_4);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_1p[1]= p2[2];

		   data2_2p[0] = p2[3];
		   data2_2p[1] = p2[4];// 2p data input
		   data2_2p[2] = p2[5];
		   data2_2p[3] = p2[6];

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x26||0x36||0x46||0x76))&&(IOSEL2_2==(0x20||0x21||0x40||0x41||0x30||0x31||0x70||0x71)))  // chip1 4to1
	   {
		   uint8_t data2_1p[4];
		   uint8_t data2_2p[1];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_4, data2_2p_1);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_1p[1] = p2[2];
		   data2_1p[2] = p2[3];
		   data2_1p[3] = p2[4];

		   data2_2p[0] = p2[5]; // 2p data input

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 1s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 1, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x26||0x36||0x46||0x76))&&(IOSEL2_2==(0x02||0x04||0x03||0x12||0x14||0x13||0x25||0x45||0x35||0x52||0x53||0x54||0x72||0x73||0x74||0x75)))  // chip1 4to2
	   {
		   uint8_t data2_1p[4];
		   uint8_t data2_2p[2];
		   p2 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_4, data2_2p_2);
		   data2_1p[0] = p2[1];  // 1p data input
		   data2_1p[1] = p2[2];
		   data2_1p[2] = p2[3];
		   data2_1p[3] = p2[4];

		   data2_2p[0] = p2[5]; // 2p data input
		   data2_2p[1] = p2[6];

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);  // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);   // 2s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
	   else if((IOSEL2_1==(0x26||0x36||0x46||0x76))&&(IOSEL2_2==(0x26||0x36||0x46||0x76)))  // chip1 4to4
	   {
		   uint8_t data2_1p[4];
		   uint8_t data2_2p[4];

		   p1 = Process_Data_1p2p_1to2(process_IC_GD_1p2p_2,data2_1p_4, data2_2p_4);
		   data2_1p[0] = p1[1];  // 1p data input
		   data2_1p[1] = p1[2];
		   data2_1p[2] = p1[3];
		   data2_1p[3] = p1[4];

		   data2_2p[0] = p1[5]; // 2p data input
		   data2_2p[1] = p1[6];
		   data2_2p[2] = p1[7];
		   data2_2p[3] = p1[8];

		   uint8_t data2_1s[2];
		   uint8_t data2_2s[2];

		   data2_1s[0] = IC_GD_Read_Reg_2(0x34);  // 1s data input
		   data2_1s[1] = IC_GD_Read_Reg_2(0x35);
		   data2_2s[0] = IC_GD_Read_Reg_2(0x34);  // 2s data input
		   data2_2s[1] = IC_GD_Read_Reg_2(0x35);

	       if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_RESET )
	       {
			   CAN_Transmit(&hcan1, TxMessage, data2_1p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_2p, (uint32_t*)CAN_TX_MAILBOX0);
			   CAN_Transmit(&hcan1, TxMessage, data2_1s, (uint32_t*)CAN_TX_MAILBOX1);
			   CAN_Transmit(&hcan1, TxMessage, data2_2s, (uint32_t*)CAN_TX_MAILBOX1);
	       }
		   else
		   {
			   HAL_UART_Transmit(&huart1, data2_1p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_2p, 4, time_out);
			   HAL_UART_Transmit(&huart1, data2_1s, 2, time_out);
			   HAL_UART_Transmit(&huart1, data2_2s, 2, time_out);
		   }
	   }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }






  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
