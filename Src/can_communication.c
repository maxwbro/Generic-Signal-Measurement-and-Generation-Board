#include "can.h"
#include "gpio.h"






void CAN_User_Init(uint16_t ID, uint8_t DLC)
{
	CAN_FilterTypeDef  sFilterConfig;
	uint8_t HAL_Status;
	/* Initialize TxHeader */

	TxMessage->StdId = ID;
	TxMessage->RTR = CAN_RTR_DATA;
	TxMessage->IDE = CAN_ID_STD;
	TxMessage->DLC = DLC;

    /* Initialize Filter */

	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.FilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);

    HAL_Status = HAL_CAN_Start(&hcan1);

    while(HAL_Status != HAL_OK)
    {
    	CAN_Start_Error();
    }
}

uint8_t CAN_Transmit(CAN_HandleTypeDef* hcan, CAN_TxHeaderTypeDef* pMsg, uint8_t* data, uint32_t* s)
{
	uint8_t HAL_Retval;
	HAL_Retval = HAL_CAN_AddTxMessage(hcan, pMsg, data, s);

	while(HAL_Retval != HAL_OK)
	{
		CAN_Transmit_Error();
	}

	return 0;
}



void CAN_Start_Error(void)
{
	LED3_Enable();   // enable LED3
	HAL_Delay(200);  // delay 200ms
	LED3_Disable(); // disable LED3
}

void CAN_Transmit_Error(void)
{
	LED3_Enable();   // enable LED3
	HAL_Delay(500);  // delay 400ms
	LED3_Disable(); // disable LED3
}

