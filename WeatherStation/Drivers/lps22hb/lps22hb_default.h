/*
 ******************************************************************************
 * @file    lps22hb_default.h
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb default: this file contains the default settings of the 
 *                            sensor after a reset. The sensor struct can be 
 *                            initialized with LPS22HB_DEFAULT_REG_VALUES
 *                            to avoid having to read the whole memory. 
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

#ifndef LPS22HB_DEFAULT_H
#define LPS22HB_DEFAULT_H

/*! \addtogroup lps22hb_default
*  lps22hb default configuration
*  @{
*/
 
#define LPS22HB_DEFAULT_REG_VALUES   \
  {  \
  .reg.interrupt_cfg.phe = LPS22HB_DISABLE,         /**< disable interrupt generation on pressure high event **/\
  .reg.interrupt_cfg.ple = LPS22HB_DISABLE,         /**< disable interrupt generation on pressure low even **/\
  .reg.interrupt_cfg.lir = LPS22HB_DISABLE,         /**< interrupt request not latched **/\
  .reg.interrupt_cfg.diff_en = LPS22HB_DISABLE,     /**< interrupt generation disabled **/\
  .reg.interrupt_cfg.reset_az = LPS22HB_DISABLE,    /**< reset Autozero function disabled **/\
  .reg.interrupt_cfg.autozero = LPS22HB_DISABLE,    /**< Autozero disabled **/\
  .reg.interrupt_cfg.reset_arp = LPS22HB_DISABLE,   /**< reset AutoRifP function disabled **/\
  .reg.interrupt_cfg.autorifp = LPS22HB_DISABLE,    /**< AutoRifP disabled **/\
  \
  .reg.ths_p = {0},                                 /**< threshold value for pressure interrupt event = 0 **/\
  \
  .reg.ctrl_reg1.sim = LPS22HB_SPI_4_WIRE,          /**< 4-wire interface **/\
  .reg.ctrl_reg1.bdu = LPS22HB_DISABLE,             /**< continuous update **/\
  .reg.ctrl_reg1.lpfp_cfg = LPS22HB_BW_9,           /**< ODR/2 with en_lpfp = 0, ODR/9 with en_lpfp = 1 **/\
  .reg.ctrl_reg1.en_lpfp = LPS22HB_DISABLE,         /**< Low-pass filter disabled **/\
  .reg.ctrl_reg1.odr = LPS22HB_POWER_DOWN_ONE_SHOT, /**< Power down / one-shot mode enabled **/\
  \
  .reg.ctrl_reg2.one_shot = LPS22HB_DISABLE,        /**< idle mode **/\
  .reg.ctrl_reg2.swreset = LPS22HB_DISABLE,         /**< normal mode **/\
  .reg.ctrl_reg2.i2c_dis = LPS22HB_DISABLE,         /**< I2C enabled **/\
  .reg.ctrl_reg2.if_add_inc = LPS22HB_ENABLE,       /**< Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI) **/\
  .reg.ctrl_reg2.stop_on_fth = LPS22HB_DISABLE,     /**<  disable FIFO watermark level use **/\
  .reg.ctrl_reg2.fifo_en = LPS22HB_DISABLE,         /**< FIFO disable **/\
  .reg.ctrl_reg2.boot = LPS22HB_DISABLE,            /**< normal mode **/\
  \
  .reg.ctrl_reg3.int_s = LPS22HB_DATA_SIGNAL,       /**< Data signal (in order of priority: DRDY or F_FTH or F_OVR or F_FSS5) **/\
  .reg.ctrl_reg3.drdy = LPS22HB_DISABLE,            /**< Disable data-ready signal on INT_DRDY pin **/\
  .reg.ctrl_reg3.f_ovr = LPS22HB_DISABLE,           /**< Disable FIFO overrun interrupt on INT_DRDY pin **/\
  .reg.ctrl_reg3.f_fth = LPS22HB_DISABLE,           /**< Disable FIFO watermark status on INT_DRDY pin **/\
  .reg.ctrl_reg3.f_fss5 = LPS22HB_DISABLE,          /**< Disable FIFO full flag on INT_DRDY pin **/\
  .reg.ctrl_reg3.pp_od = LPS22HB_PP,                /**< Push-pull selection on interrupt pads **/\
  .reg.ctrl_reg3.int_h_l = LPS22HB_INT_H,           /**< Interrupt active-high **/\
  \
  .reg.fifo_ctrl.wtm = 0,                           /**< FIFO watermark level selection = 0 **/\
  .reg.fifo_ctrl.f_mode = LPS22HB_BYPASS,           /**< Bypass mode **/\
  \
  .reg.ref_p = {0},                                 /**< Reference pressure = 0 **/\
  \
  .reg.rpds = {0},                                  /**< Pressure offset = 0 **/\
  \
  .reg.res_conf.lc_en = LPS22HB_DISABLE,            /**< Normal mode (low-noise mode) **/\
   }

/*! @} */

#endif /* LPS22HB_DEFAULT_H */
