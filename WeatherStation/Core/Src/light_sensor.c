#include "light_sensor.h"
#include "math.h"

#define ADC_TIMEOUT 1000
#define ADC_BIT_RESOLUTION 12

uint32_t read_adc(ADC_HandleTypeDef *hadc, void (*error_handler)()) {

	uint32_t value = 0;

	/* Start ADC conversion */
	if (HAL_ADC_Start(hadc) != HAL_OK) {
		error_handler();
	}

	/* Wait conversion till conversion has finished */
	if (HAL_ADC_PollForConversion(hadc, ADC_TIMEOUT) != HAL_OK) {
		error_handler();
	}

	/* Read value conversion result */
	value = HAL_ADC_GetValue(hadc);

	/* Stop ADC conversion */
	if (HAL_ADC_Stop(hadc) != HAL_OK) {
		error_handler();
	}

	return value;
}

/* Returns a light intensity as a fraction (0=complete darkness, 1=daylight) */
float read_light_sensor(ADC_HandleTypeDef *hadc, void (*error_handler)()) {
	uint32_t sensor_value = read_adc(hadc, error_handler);

	// Convert raw ADC value to light value
	float R_sensor = (float)sensor_value / (pow(2, ADC_BIT_RESOLUTION)-1);
	return R_sensor;
}
