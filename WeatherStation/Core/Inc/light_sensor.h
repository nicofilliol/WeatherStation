#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include "stm32l4xx_hal.h"

uint32_t read_adc(ADC_HandleTypeDef *hadc, void (*error_handler)());
float read_light_sensor(ADC_HandleTypeDef *hadc, void (*error_handler)());

#endif
