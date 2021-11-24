/*
 * DHT22.h
 *
 *  Created on: 24 Nov 2021
 *      Author: joelasper
 */
#include "stm32l4xx_hal.h"

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#define TEMP_HUM_SENSOR_PIN_Pin GPIO_PIN_0
#define TEMP_HUM_SENSOR_PIN_GPIO_Port GPIOB

void DHT22_Start(void);
uint8_t DHT22_Check_Response(void);
uint8_t DHT22_Read(void);
void Set_Pin_Input(void);
void Set_Pin_Output(void);


#endif /* INC_DHT22_H_ */
