/*
 * DHT22.c
 *
 *  Created on: 24 Nov 2021
 *      Author: joelasper
 */
#include "DHT22.h"

void Set_Pin_Input(void);
void Set_Pin_Output(void);

// https://controllerstech.com/temperature-measurement-using-dht22-in-stm32/
void DHT22_Start(void){
	Set_Pin_Output(); // set the pin as output
	HAL_GPIO_WritePin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin, 0);   // pull the pin low
	HAL_Delay(1200);   // wait for > 1ms

	HAL_GPIO_WritePin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin, 1);   // pull the pin high
	HAL_Delay(20);   // wait for 30us

	Set_Pin_Input();   // set as input
}

uint8_t DHT22_Check_Response(void){
	Set_Pin_Input();   // set as input
	uint8_t Response = 0;
	HAL_Delay(40);  // wait for 40us
	if (!(HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin))) // if the pin is low
	{
		HAL_Delay(80);   // wait for 80us
		if ((HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin))) Response = 1;  // if the pin is high, response is ok
		else Response = -1;
	}

	while ((HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin)));   // wait for the pin to go low
	return Response;
}

uint8_t DHT22_Read(void){
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin)));   // wait for the pin to go high
		HAL_Delay(40);   // wait for 40 us

		if (!(HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin(TEMP_HUM_SENSOR_PIN_GPIO_Port, TEMP_HUM_SENSOR_PIN_Pin)));  // wait for the pin to go low
	}

	return i;
}

void Set_Pin_Input(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : TEMP_HUM_SENSOR_PIN_Pin */
	GPIO_InitStruct.Pin = TEMP_HUM_SENSOR_PIN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TEMP_HUM_SENSOR_PIN_GPIO_Port, &GPIO_InitStruct);
}

void Set_Pin_Output(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : TEMP_HUM_SENSOR_PIN_Pin */
	GPIO_InitStruct.Pin = TEMP_HUM_SENSOR_PIN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TEMP_HUM_SENSOR_PIN_GPIO_Port, &GPIO_InitStruct);
}

