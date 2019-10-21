#include "spi.h"
#include "can.h"
#include "gpio.h"


/* process data function in different situations (1p's bytes(1,2,4) to 2p's bytes(1,2,4))*/
//
//
// opcode is operation code can be found in spi.h
// data_1p for channel1 primary
// data_2p for channel2 primary
//
//

/*process data, 1p-2p data type 1-1*/
uint8_t* Process_Data_1p2p_1to1(uint8_t opcode, uint8_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[3];

	uint8_t cmd[3] = {opcode, data_1p, data_2p};
	HAL_SPI_Transmit(&hspi1, cmd, 3, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 3, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 1-2*/
uint8_t* Process_Data_1p2p_1to2(uint8_t opcode, uint8_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[4];

	uint8_t cmd[4];
	cmd[0] = opcode;
	cmd[1] = data_1p;
	cmd[2] = (uint8_t)(data_2p >> 8);
	cmd[3] = (uint8_t)(data_2p);

	HAL_SPI_Transmit(&hspi1, cmd, 4, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 4, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 1-4*/
uint8_t* Process_Data_1p2p_1to4(uint8_t opcode, uint8_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[6];

	uint8_t cmd[6];
	cmd[0] = opcode;
	cmd[1] = data_1p;
	cmd[2] = (uint8_t)(data_2p >> 24);
	cmd[3] = (uint8_t)(data_2p >> 16);
	cmd[4] = (uint8_t)(data_2p >> 8);
	cmd[5] = (uint8_t)data_2p;

	HAL_SPI_Transmit(&hspi1, cmd, 6, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 6, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable(); // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 2-1*/
uint8_t* Process_Data_1p2p_2to1(uint8_t opcode, uint16_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	static uint8_t Input[4];

	uint8_t cmd[4];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 8);
	cmd[2] = (uint8_t)data_1p;
	cmd[3] = data_2p;

	HAL_SPI_Transmit(&hspi1, cmd, 4, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 4, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 2-2*/
uint8_t* Process_Data_1p2p_2to2(uint8_t opcode, uint16_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	static uint8_t Input[5];

	uint8_t cmd[4];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 8);
	cmd[2] = (uint8_t)(data_1p);
	cmd[3] = (uint8_t)(data_2p >> 8);
	cmd[4] = (uint8_t)(data_2p);

	HAL_SPI_Transmit(&hspi1, cmd, 5, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 5, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 2-4*/
uint8_t* Process_Data_1p2p_2to4(uint8_t opcode, uint16_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[7];

	uint8_t cmd[7];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 8);
	cmd[2] = (uint8_t)data_1p;
	cmd[3] = (uint8_t)(data_2p >> 24);
	cmd[4] = (uint8_t)(data_2p >> 16);
	cmd[5] = (uint8_t)(data_2p >> 8);
	cmd[6] = (uint8_t)data_2p;

	HAL_SPI_Transmit(&hspi1, cmd, 7, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 7, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable(); // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 4-1*/
uint8_t* Process_Data_1p2p_4to1(uint8_t opcode, uint32_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[6];

	uint8_t cmd[6];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 24);
	cmd[2] = (uint8_t)(data_1p >> 16);
	cmd[3] = (uint8_t)(data_1p >> 8);
	cmd[4] = (uint8_t)data_1p;
	cmd[5] = data_2p;

	HAL_SPI_Transmit(&hspi1, cmd, 6, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 6, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable(); // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 4-2*/
uint8_t* Process_Data_1p2p_4to2(uint8_t opcode, uint32_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	static uint8_t Input[7];

	uint8_t cmd[7];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 24);
	cmd[2] = (uint8_t)(data_1p >> 16);
	cmd[3] = (uint8_t)(data_1p >> 8);
	cmd[4] = (uint8_t)(data_1p);
	cmd[5] = (uint8_t)(data_2p >> 8);
	cmd[6] = (uint8_t)(data_2p);

	HAL_SPI_Transmit(&hspi1, cmd, 7, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 7, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input;
}

/*process data, 1p-2p data type 4-4*/
uint8_t* Process_Data_1p2p_4to4(uint8_t opcode, uint32_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	static uint8_t Input[9];

	uint8_t cmd[9];
	cmd[0] = opcode;
	cmd[1] = (uint8_t)(data_1p >> 24);
	cmd[2] = (uint8_t)(data_1p >> 16);
	cmd[3] = (uint8_t)(data_1p >> 8);
	cmd[4] = (uint8_t)(data_1p);
	cmd[5] = (uint8_t)(data_2p >> 24);
    cmd[6] = (uint8_t)(data_2p >> 16);
	cmd[7] = (uint8_t)(data_2p >> 8);
	cmd[8] = (uint8_t)(data_2p);

	HAL_SPI_Transmit(&hspi1, cmd, 9, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 9, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable(); // disable iC-GD

   return Input;
}

uint8_t* Process_Data_1p2p_bc(uint8_t data_1_1p, uint8_t data_1_2p, uint8_t data_2_1p, uint8_t data_2_2p)
{
	IC_GD_Enable();  // enable iC-GD

	static uint8_t Input[5];

	uint8_t cmd[5] = {process_IC_GD_1p2p, data_2_1p, data_2_1p, data_1_1p, data_1_2p};
    HAL_SPI_Transmit(&hspi1, cmd, 5, time_out);

    while (HAL_SPI_Receive(&hspi1, Input, 5, time_out) != HAL_OK)
    {
    	IC_GD_read_Error();
    }

	IC_GD_Disable();  // disable iC-GD

    return Input;
}

//
//
/* read/write register function */

uint8_t IC_GD_Write_Reg_1(uint8_t reg, uint8_t value)
{

	IC_GD_Enable();  // enable iC-GD

    uint8_t cmd[3] = {write_IC_GD_CMD_1, reg, value};
    while(HAL_SPI_Transmit(&hspi1, cmd, 3, time_out) != HAL_OK)
    {
        IC_GD_write_Error();
    }

    IC_GD_Disable();  // disable iC-GD

    return cmd[3];

}

uint8_t IC_GD_Read_Reg_1(uint8_t reg)
{
	uint8_t reg_val[4];

	IC_GD_Enable();  // enable iC-GD

	uint8_t cmd[2] = {read_IC_GD_CMD_1, reg};
	HAL_SPI_Transmit(&hspi1, cmd, 2, time_out);

	while(HAL_SPI_Receive(&hspi1, reg_val, 4, time_out) != HAL_OK)
	{
		IC_GD_read_Error();
	}

	IC_GD_Disable();  // disable iC-GD


	return reg_val[3];
}

uint8_t IC_GD_Write_Reg_2(uint8_t reg, uint8_t value)
{

	IC_GD_Enable();  // enable iC-GD

    uint8_t cmd[3] = {write_IC_GD_CMD_2, reg, value};
    HAL_SPI_Transmit(&hspi1, cmd, 3, time_out);

    while(HAL_SPI_Transmit(&hspi1, cmd, 3, time_out) != HAL_OK)
    {
    	IC_GD_write_Error();
    }
    IC_GD_Disable();  // disable iC-GD

    return cmd[3];

}

uint8_t IC_GD_Read_Reg_2(uint8_t reg)
{
	uint8_t reg_val[4];

	IC_GD_Enable();   // enable iC-GD

	uint8_t cmd[2] = {read_IC_GD_CMD_2, reg};
	HAL_SPI_Transmit(&hspi1, cmd, 2, time_out);

	while(HAL_SPI_Receive(&hspi1, reg_val, 4, time_out) != HAL_OK)
   {
	    IC_GD_read_Error();
   }
	IC_GD_Disable();  // enable iC-GD

	return reg_val[3];
}

/* register initialization */

void IC_GD_Reg_Init(uint8_t reg_address[BUFFERSIZE], uint8_t reg_val1[BUFFERSIZE], uint8_t reg_val2[BUFFERSIZE])
{
	int i = 0;
	while (i<BUFFERSIZE)
	  {
		  IC_GD_Write_Reg_1(reg_address[i],reg_val1[i]);
		  IC_GD_Write_Reg_2(reg_address[i],reg_val2[i]);
	  }
}

/* error handler (LED TOGGLING in 200ms)*/


void IC_GD_read_Error(void)
{
    LED2_Enable();   // enable LED1
    HAL_Delay(200);  // delay 200ms
    LED2_Disable(); // disable LED1
}

void IC_GD_write_Error(void)
{
    LED1_Enable();   // enable LED1
    HAL_Delay(200);  // delay 200ms
    LED1_Disable(); // disable LED1
}

