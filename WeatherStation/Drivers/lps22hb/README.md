# README

## Driver for ST's sensor LPS22HB, an ultra-compact piezoresistive absolute pressure sensor which functions as a digital output barometer.

#### This driver is based on the 08.06.2021 version of the LSM6DSM driver written by Federico Villani.

#### TODO: ensure correct writing of reg RES_CONF (0x1A) with reserved bit1 that should not change

## Example code for STM 

```c
/* USER CODE BEGIN Includes */
#include "lps22hb.h"
#include "lps22hb_ex.h"
/* USER CODE END Includes */

...
lps22hb_t lps22hb = LPS22HB_DEFAULT_REG_VALUES;

lps22hb_err_t lps22hb_read(uint8_t reg, uint8_t *buf, uint8_t bytes);
lps22hb_err_t lps22hb_write(uint8_t reg, uint8_t *buf, uint8_t bytes);
...
int main(void)
{
  
  lps22hb.comm.read = lps22hb_read;  
  lps22hb.comm.write= lps22hb_write; 

  lps22hb_err_t err;

  err = lps22hb_setup_communication(&lps22hb, LPS22HB_SPI_3_WIRE); //enables SPI 3-wire


  lps22hb.reg.ctrl_reg1.odr = LPS22HB_ODR_1Hz; //turns on the sensor
  lps22hb_write_reg(&lps22hb, LPS22HB_CTRL_REG1);

  while (1)
  {
    float pressure = 0;
    float temperature = 0;
	  HAL_Delay(1000);

	  lps22hb_read_reg(&lps22hb, LPS22HB_STATUS);
	  if(lps22hb.reg.status.p_da){ //check if pressure data is available
		    err |= lps22hb_get_press_data(&lps22hb, &pressure); //read the data, and save in pressure as hPa
	  }
	  if(lps22hb.reg.status.t_da){ //check if temperature data is available
		    err |= lps22hb_get_temp_data(&lps22hb, &temperature); //read the data, and save in pressure as Celsius
	  }
  }
}
...


lps22hb_err_t lps22hb_read(uint8_t reg, uint8_t *buf, uint8_t bytes){
/* Set CS pin low, sensor enters SPI mode, lps22hb selected for communication */
	lps22hb_err_t err = LPS22HB_SUCCESS;
	HAL_GPIO_WritePin(CS_P_GPIO_Port, CS_P_Pin, GPIO_PIN_RESET);
	reg|=1<<7;
	/* Write register to be read to the sensor, masked with 0x80 indicating read command */
	err |= HAL_SPI_Transmit(&hspi2, &(reg), 1, 1000);
	err |= HAL_SPI_Receive(&hspi2, buf, bytes, 1000);
	/* Set CS pin high, free 3-wire SPI for other communication */
	HAL_GPIO_WritePin(CS_P_GPIO_Port, CS_P_Pin, GPIO_PIN_SET);
	return err;
}
lps22hb_err_t lps22hb_write(uint8_t reg, uint8_t *buf, uint8_t bytes){
	lps22hb_err_t err = LPS22HB_SUCCESS;
	HAL_GPIO_WritePin(CS_P_GPIO_Port, CS_P_Pin, GPIO_PIN_RESET);
	err |=	HAL_SPI_Transmit(&hspi2, &reg, 1, 1000);
	err |=	HAL_SPI_Transmit(&hspi2, buf, bytes, 1000);
	HAL_GPIO_WritePin(CS_P_GPIO_Port, CS_P_Pin, GPIO_PIN_SET);
	return err;
}
```

