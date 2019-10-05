#include "spi.h"
#include "can.h"
#include "gpio.h"

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

uint8_t reg_address_2[BUFFERSIZE] ={
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1B,
		0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x39, 0x3A, 0x3B, 0x3D,
		0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,

};

uint8_t reg_val_2[BUFFERSIZE] ={
		VI_DO, 0x03, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70,
		VI_CO, 0x03, 0x07, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xA6, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

/* process data function in different situations (1p's bytes(1,2,4) to 2p's bytes(1,2,4))*/
//
//
// opcode is operation code can be found in spi.h
// data_1p for channel1 primary
// data_2p for channel2 primary
//
//

/*process data, 1p-2p data type 1-1*/
uint8_t Process_Data_1p2p_1to1(uint8_t opcode, uint8_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[3];

	uint8_t cmd[3] = {opcode, data_1p, data_2p};
	HAL_SPI_Transmit(&hspi1, cmd, 3, time_out);

	while (HAL_SPI_Receive(&hspi1, Input, 3, time_out) != HAL_OK)
	{
	    IC_GD_read_Error();
	}

   IC_GD_Disable();  // disable iC-GD

   return Input[3];
}

/*process data, 1p-2p data type 1-2*/
uint8_t Process_Data_1p2p_1to2(uint8_t opcode, uint8_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[4];

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

   return Input[4];
}

/*process data, 1p-2p data type 1-4*/
uint8_t Process_Data_1p2p_1to4(uint8_t opcode, uint8_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[6];

	uint8_t cmd[4];
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

   return Input[6];
}

/*process data, 1p-2p data type 2-1*/
uint8_t Process_Data_1p2p_2to1(uint8_t opcode, uint16_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	uint8_t Input[4];

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

   return Input[6];
}

/*process data, 1p-2p data type 2-2*/
uint8_t Process_Data_1p2p_2to2(uint8_t opcode, uint16_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	uint8_t Input[5];

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

   return Input[5];
}

/*process data, 1p-2p data type 2-4*/
uint8_t Process_Data_1p2p_2to4(uint8_t opcode, uint16_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[7];

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

   return Input[7];
}

/*process data, 1p-2p data type 4-1*/
uint8_t Process_Data_1p2p_4to1(uint8_t opcode, uint32_t data_1p, uint8_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[6];

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

   return Input[6];
}

/*process data, 1p-2p data type 4-2*/
uint8_t Process_Data_1p2p_4to2(uint8_t opcode, uint32_t data_1p, uint16_t data_2p)
{
	IC_GD_Enable(); // enable iC-GD

	uint8_t Input[7];

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

   IC_GD_Disable();

   return Input[7];  // disable iC-GD
}

/*process data, 1p-2p data type 4-4*/
uint8_t Process_Data_1p2p_4to4(uint8_t opcode, uint32_t data_1p, uint32_t data_2p)
{
	IC_GD_Enable();  // enable iC-GD

	uint8_t Input[9];

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

   return Input[9];
}

uint8_t Process_Data_1p2p_bc(uint8_t data_1_1p, uint8_t data_1_2p, uint8_t data_2_1p, uint8_t data_2_2p)
{
	IC_GD_Enable();  // enable iC-GD

	uint8_t Input[5];

	uint8_t cmd[5] = {process_IC_GD_1p2p, data_2_1p, data_2_1p, data_1_1p, data_1_2p};
    HAL_SPI_Transmit(&hspi1, cmd, 5, time_out);

    while (HAL_SPI_Receive(&hspi1, Input, 5, time_out) != HAL_OK)
    {
    	IC_GD_read_Error();
    }

	IC_GD_Disable();  // disable iC-GD

    return Input[5];
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

void IC_GD_Reg_Init(void)
{
	int i = 0;
	while (i<BUFFERSIZE)
	  {
		  IC_GD_Write_Reg_1(reg_address_1[i],reg_val_1[i]);
		  IC_GD_Write_Reg_2(reg_address_2[i],reg_val_2[i]);
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
