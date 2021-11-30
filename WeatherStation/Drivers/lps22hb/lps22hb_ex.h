/*
 ******************************************************************************
 * @file    lps22hb_ex.h
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb expansion functions: This file contains expansion function 
 *              that help with reading, conversion of measurements and 
 *              advanced configurations
 ******************************************************************************
 * @attention
 *
 * Beautiful license
 *
 ******************************************************************************
 */

#ifndef LPS22HB_EX_H
#define LPS22HB_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lps22hb.h"

/*! @defgroup lps22hb_XL_GY_functions Group: XL GY functions  
*  lps22hb accelerometer and gyroscope functions
*  @{
*/

/**
 * @brief Calculate the pressure value in hPa from the value stored in the 
 *        pressure-sensor registers in configs->reg.  
 * 
 * @param configs         user defined lps22hb_t struct (ptr)
 * @param P               pointer to storage buffer of type float a to store the calculated data 
 * @return lps22hb_err_t  error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_calc_press_data_hPa(lps22hb_t *configs, float * P);

/**
 * @brief Calculate the tempertaure value in ºC from the value stored in the 
 *        sensor registers in configs->reg.  
 * 
 * @param configs         user defined lps22hb_t struct (ptr)
 * @param T                 pointer to storage buffer of type float to store the calculated data 
 * @return lps22hb_err_t  error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_calc_temp_data_C(lps22hb_t *configs, float* T);

/**
 * @brief Read the pressure data from the sensor, store the raw data in the user struct and store the
 *        calculated data in the P buffer in hPa
 * 
 * @param configs         user defined lps22hb_t struct (ptr)
 * @param P               pointer to storage buffer of type float a to store the calculated data 
 * @return lps22hb_err_t  error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_get_press_data(lps22hb_t *const configs, float * P);

/**
 * @brief Read the temperature data from the sensor, store the raw data in the user struct and store the
 *        calculated data in the T buffer in Celsius
 * 
 * @param configs         user defined lps22hb_t struct (ptr)
 * @param T               pointer to storage buffer of type float to store the calculated data 
 * @return lps22hb_err_t  error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_get_temp_data(lps22hb_t *const configs, float* T);

/*! @} */

#ifdef __cplusplus
}
#endif

#endif /* LPS22HB_EX_H */