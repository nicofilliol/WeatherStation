/*
 ******************************************************************************
 * @file    lps22hb_ex.c
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb expansion functions: This file contains expansion function 
 *              that help with reading, conversion of measurements and 
 *              advanced configurations
 ******************************************************************************
 * @attention
 *
 *  Copyright (c) 2021 UDD Team - Jacopo Graldi. 
 *  All rights reserved.
 *  This work is licensed under the terms of the MIT license.  
 *  For a copy, see <https://opensource.org/licenses/MIT> or
 *  appended LICENSE file.
 *
 ******************************************************************************
 */
#include "lps22hb_ex.h"

lps22hb_err_t lps22hb_calc_press_data_hPa(lps22hb_t *const configs, float* P)
{
    uint8_t* P_raw = (uint8_t *)configs->reg.press_out;
    /* Build 24bit two's complement in 32bit  */
    uint32_t P_32bits = (((uint32_t)P_raw[2]) << 16) | ((uint32_t) P_raw[1] << 8) | (uint32_t) P_raw[0];
    P_32bits = (int32_t)(P_32bits<<8)>>8;

    /* Calculate pressure in hPa */
    *P = ((float)P_32bits) / 4096;
    return LPS22HB_SUCCESS;
}

lps22hb_err_t lps22hb_calc_temp_data_C(lps22hb_t* const configs, float* T)
{
    /* build 16 bit temperature raw value in two's comlement */
    uint8_t* T_raw = (uint8_t*)configs->reg.temp_out;
    uint16_t T_16bits = (((uint8_t)T_raw[1]) << 8) | ((uint8_t) T_raw[0]);
    /* Calculate temperature in  °C */
    *T = (((float)T_16bits) / 100);
    return LPS22HB_SUCCESS;
}

lps22hb_err_t lps22hb_get_press_data(lps22hb_t *const configs, float *P)
{
    lps22hb_err_t err = LPS22HB_SUCCESS;
    err |= lps22hb_read_reg(configs, LPS22HB_STATUS);
    if (configs->reg.status.p_da)
    {
        err |= lps22hb_read_regs(configs, LPS22HB_PRESS_OUT_XL, 3);
        err |= lps22hb_calc_press_data_hPa(configs, P);
        return err;
    }
    return LPS22HB_NO_NEW_DATA;
}

lps22hb_err_t lps22hb_get_temp_data(lps22hb_t *const configs, float* T)
{
    lps22hb_err_t err = LPS22HB_SUCCESS;
    err |= lps22hb_read_reg(configs, LPS22HB_STATUS);
    if (configs->reg.status.t_da)
    {
        err |= lps22hb_read_regs(configs, LPS22HB_TEMP_OUT_L, 2);
        err |= lps22hb_calc_temp_data_C(configs, T);
        return err;
    }
    return LPS22HB_NO_NEW_DATA;
}
