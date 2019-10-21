#include "gpio.h"
#include "spi.h"
void mode_setting()
{

	int PB4 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
	int PB5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
	int PB8 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
	int PB9 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
	int PB10 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	int PB11 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
	int PB12 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
	int PB13 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
	int PB14 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
	int PB15 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);

		while(PB4 == GPIO_PIN_RESET) // skip initialisation if pin 4 activated
		{
			//4 is used to enter configuration mode, 5 is used for writing to EEPROM, 6 and 7 is for frequency selection 8,9 are used to select which code input, 10-15 are programming

			/* icgd 0 channel 1 */

			if(PB8 == GPIO_PIN_RESET && PB9 == GPIO_PIN_RESET) //channel 1 config line 1
			{
				//15 is envif_1
				//d0 is 0 no output
				//12,13,14 are io_sel_1p
				if(PB9 == GPIO_PIN_RESET && PB10 == GPIO_PIN_RESET)
				{
					dip_write_register_1(0x00,PB15,1,1,1,0,PB14,PB13,PB12);
				}
				else
				{
					dip_write_register_1(0x00,PB15,0,0,0,0,PB14,PB13,PB12);
				}
				//10,11 di select_1
				dip_write_register_1(0x01,0,0,0,0,0,0,PB11,PB10);
				//vici_1 is set to +-10v (000)

				//CO_sel_1 is set to 0-20mv (00_
				dip_write_register_1(0x02,0,0,0,0,0,0,0,0);

			}

			/* ic-gd 0 channel 2 */

			if(PB8 == GPIO_PIN_SET && PB9 == GPIO_PIN_RESET)
			{
				//15 is envif_1
				//d0 is 0 no output
				//12,13,14 are io_sel_1p
				if(PB9 == GPIO_PIN_RESET && PB10 == GPIO_PIN_RESET)
				{
					dip_write_register_1(0x10,PB15,1,1,1,0,PB14,PB13,PB12);
				}
				else
				{
					dip_write_register_1(0x00,PB15,0,0,0,0,PB14,PB13,PB12);
				}
				//10,11 di select_1
				dip_write_register_1(0x11,0,0,0,0,0,0,PB11,PB10);
				//vici_1 is set to +-10v (000)
				//CO_sel_1 is set to 0-20mv (00_
				dip_write_register_1(0x12,0,0,0,0,0,0,0,0);

			}
			//icgd 1 channel 1

			if(PB8 == GPIO_PIN_RESET && PB9 == GPIO_PIN_SET)
			{
				//15 is envif_1
				//d0 is 0 no output
				//12,13,14 are io_sel_1p
				if(PB9 == GPIO_PIN_RESET && PB10 == GPIO_PIN_RESET)
				{
					dip_write_register_2(0x00,PB15,1,1,1,0,PB14,PB13,PB12);
				}
				else
				{
					dip_write_register_2(0x00,PB15,0,0,0,0,PB14,PB13,PB12);
				}
				//10,11 di select_1
				dip_write_register_2(0x01,0,0,0,0,0,0,PB11,PB10);

				//vici_1 is set to +-10v (000)
				//CO_sel_1 is set to 0-20mv (00_)
				dip_write_register_2(0x02,0,0,0,0,0,0,0,0);

			}

			}
			//ic-gd 1 channel 2
			if(PB8 == GPIO_PIN_SET && PB9 == GPIO_PIN_SET)
			{
				//15 is envif_1
				//d0 is 0 no output
				//12,13,14 are io_sel_1p
				if(PB9 == GPIO_PIN_RESET && PB10 == GPIO_PIN_RESET)
				{
					dip_write_register_2(0x10,PB15,1,1,1,0,PB14,PB13,PB12);
				}
				else
				{
					dip_write_register_2(0x10,PB15,0,0,0,0,PB14,PB13,PB12);
				}
				//10,11 di select_1
				dip_write_register_2(0x11,0,0,0,0,0,0,PB11,PB10);
				//vici_1 is set to +-10v (000)
				//CO_sel_1 is set to 0-20mv (00_
				dip_write_register_2(0x12,0,0,0,0,0,0,0,0);
			}

	If( PB5 == GPIO_PIN_SET)
	{
		dip_write_register_1(0x40,1,0,0,1,0,1,1,0)
		dip_write_register_2(0x40,1,0,0,1,0,1,1,0)
	}
}



uint8_t dip_write_register_1(uint8_t reg, int a, int b, int c, int d, int e, int f, int g, int h)
{
	uint8_t status;
	uint8_t byte_send = a*128+b*64+c*32+d*16+e*8+f*4+g*2+h;
    status = IC_GD_Write_Reg_1(reg, byte_send);
	return status;
}

uint8_t dip_write_register_2(uint8_t reg, int a, int b, int c, int d, int e, int f, int g, int h)
{
	uint8_t status;
	uint8_t byte_send = a*128+b*64+c*32+d*16+e*8+f*4+g*2+h;
    status = IC_GD_Write_Reg_2(reg, byte_send);
	return status;
}
