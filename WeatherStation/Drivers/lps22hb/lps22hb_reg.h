/*
 ******************************************************************************
 * @file    lps22hb_reg.h
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb registers: this file contains the address of the registers,
 *                             enums for register settings and bitfield structs
 *                             for the setting registers 
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

#ifndef LPS22HB_REG_H
#define LPS22HB_REG_H

/*************** INCLUDE ***************/
#include <stdint.h> 


/*! @defgroup lps22hb_registers Group: registers    
*  lps22hb registers
*  @{
*/

/*********** REGISTERS ***********/

/* Setup registers */
#define LPS22HB_INTERRUPT_CFG       (uint8_t)0x0BU         /**< Interrupt mode for pressure acquisition configuration. (r/w)**/
#define LPS22HB_THS_P_L             (uint8_t)0x0CU         /**< User-defined threshold value for pressure interrupt event (Least significant bits). (r/w) **/
#define LPS22HB_THS_P_H             (uint8_t)0x0DU         /**< User-defined threshold value for pressure interrupt event (Most significant bits). (r/w) **/
#define LPS22HB_WHO_AM_I            (uint8_t)0x0FU         /**< Device Who am I (r) **/
#define LPS22HB_CTRL_REG1           (uint8_t)0x10U         /**< Control register 1 (r/w) **/
#define LPS22HB_CTRL_REG2           (uint8_t)0x11U         /**<  Control register 2 (r/w) **/
#define LPS22HB_CTRL_REG3           (uint8_t)0x12U         /**< Control register 3 - INT_DRDY pin control register (r/w) **/
#define LPS22HB_FIFO_CTRL           (uint8_t)0x14U         /**< FIFO control register (r/w) **/
#define LPS22HB_REF_P_XL            (uint8_t)0x15U         /**< Reference pressure (LSB data) (r/w) **/
#define LPS22HB_REF_P_L             (uint8_t)0x16U         /**< Reference pressure (middle part) (r/w) **/
#define LPS22HB_REF_P_H             (uint8_t)0x17U         /**< Reference pressure (MSB part) (r/w) **/
#define LPS22HB_RPDS_L              (uint8_t)0x18U         /**< Pressure offset (LSB data) (r/w) **/
#define LPS22HB_RPDS_H              (uint8_t)0x19U         /**< Pressure offset (MSB data) (r/w) **/
#define LPS22HB_RES_CONF            (uint8_t)0x1AU         /**< Low-power mode configuration. Read this register before writing it in order to know bit1 and not to change it (r/w) **/
#define LPS22HB_INT_SOURCE          (uint8_t)0x25U         /**< Interrupt source (r) **/
#define LPS22HB_FIFO_STATUS         (uint8_t)0x26U         /**< FIFO_STATUS (r) **/
#define LPS22HB_STATUS              (uint8_t)0x27U         /**< STATUS register (r) **/
#define LPS22HB_PRESS_OUT_XL        (uint8_t)0x28U         /**< Pressure output value (LSB) (r) **/
#define LPS22HB_PRESS_OUT_L         (uint8_t)0x29U         /**< Pressure output value (mid part) (r) **/
#define LPS22HB_PRESS_OUT_H         (uint8_t)0x2AU         /**< Pressure output value (MSB) (r) **/
#define LPS22HB_TEMP_OUT_L          (uint8_t)0x2BU         /**< Temperature output value (LSB) (r) **/
#define LPS22HB_TEMP_OUT_H          (uint8_t)0x2CU         /**< Temperature output value (MSB) (r) **/
#define LPS22HB_LPFP_RES            (uint8_t)0x33U         /**< Low-pass filter reset register. (r) **/
/*! @} */

/*! @defgroup lps22hb_settings Group: settings    
*  lps22hb settings
*  @{
*/

/*! @enum enable_disable_t Enum: disable     
* @{
*/
typedef enum{
  LPS22HB_ENABLE  = 1,   /**< Enable Register  **/
  LPS22HB_DISABLE = 0,  /**< Disable Register **/
} lps22hb_en_dis_t;
/*! @} */

/*! @enum lps22hb_odr_t Enum: odr     
* @{
*/
typedef enum{
  LPS22HB_POWER_DOWN_ONE_SHOT  =  0,   /**< Power down / one-shot mode enabled  **/
  LPS22HB_ODR_1Hz  =  1,  
  LPS22HB_ODR_10Hz  =  2, 
  LPS22HB_ODR_25Hz  =  3, 
  LPS22HB_ODR_50Hz  =  4, 
  LPS22HB_ODR_75Hz  =  5, 
} lps22hb_odr_t;
/*! @} */

/*! @enum lps22hb_lpfp_cfg_t Enum:  lpfp_cfg    
* @{
*/
typedef enum{
  LPS22HB_BW_9   =  0,   /**<  Device BW if EN_LPFP = 1: ODR/9 **/
  LPS22HB_BW_20  =  1,   /**<  Device BW if EN_LPFP = 1: ODR/20 **/

} lps22hb_lpfp_cfg_t;
/*! @} */

/*! @enum lps22hb_sim_t Enum: sim     
* @{
*/
typedef enum{
  LPS22HB_SPI_4_WIRE  =  0,   
  LPS22HB_SPI_3_WIRE  =  1,   
} lps22hb_sim_t;
/*! @} */

/*! @enum lps22hb_int_s_t Enum:  int_s    
* @{
*/
typedef enum{
  LPS22HB_DATA_SIGNAL  =  0,   /**<  Data signal (in order of priority: DRDY or F_FTH or F_OVR or F_FSS5 **/
  LPS22HB_P_HIGH       =  1,   /**<  Pressure high (P_high **/
  LPS22HB_P_LOW        =  2,   /**< Pressure low (P_low)  **/
  LPS22HB_P_HIGH_LOW   =  3,   /**<  Pressure low OR high **/
} lps22hb_int_s_t;
/*! @} */

/*! @enum lps22hb_pp_od_t Enum: pp_od     
* @{
*/
typedef enum{
  LPS22HB_PP  = 0,   /**< Push pull  **/
  LPS22HB_OD  = 1,  /**< Open drain **/
} lps22hb_pp_od_t;
/*! @} */

/*! @enum lps22hb_int_h_l_t Enum: int_h_l     
* @{
*/
typedef enum{
  LPS22HB_INT_H  = 0,   /**< Interrupt active high  **/
  LPS22HB_INT_L  = 1,  /**< Interrupt active low **/
} lps22hb_int_h_l_t;
/*! @} */

/*! @enum lps22hb_f_mode_t Enum:  fmode    
* @{
*/
typedef enum{
  LPS22HB_BYPASS            =  0,    
  LPS22HB_FIFO              =  1,    
  LPS22HB_STREAM            =  2,    
  LPS22HB_STREAM_TO_FIFO    =  3,    
  LPS22HB_BYPASS_TO_STREAM  =  4,    
  LPS22HB_DYNAMIC_STREAM    =  6,    
  LPS22HB_BYPASS_TO_FIFO    =  7,    
} lps22hb_f_mode_t;
/*! @} */

/*! @} */

/*! @defgroup lps22hb_structs Group: structs    
*  lps22hb structs
*  @{
*/

typedef struct {
  uint8_t phe                  : 1;  /**< Enable interrupt generation on pressure high event **/
  uint8_t ple                  : 1;  /**< Enable interrupt generation on pressure low event **/
  uint8_t lir                  : 1;  /**< Latch interrupt request to the INT_SOURCE (25h) register **/
  uint8_t diff_en              : 1;  /**< Enable interrupt generation **/
  uint8_t reset_az             : 1;  /**< Reset Autozero function. **/
  uint8_t autozero             : 1;  /**< Enable Autozero function **/
  uint8_t reset_arp            : 1;  /**< Reset AutoRifP function **/
  uint8_t autorifp             : 1;  /**< Enable AUTORIFP: function **/
} lps22hb_interrupt_cfg_t;

typedef struct {
  uint8_t sim                  : 1;  /**< SPI Serial Interface Mode selection **/
  uint8_t bdu                  : 1;  /**< Block data update **/
  uint8_t lpfp_cfg             : 1;  /**< LPFP_CFG: Low-pass configuration register. **/
  uint8_t en_lpfp              : 1;  /**< Enable low-pass filter on pressure data when Continuous mode is used **/
  uint8_t odr                  : 3;  /**< Output data rate selection **/
  uint8_t                      : 1;  /**< RESERVED **/
} lps22hb_ctrl_reg1_t;

typedef struct {
  uint8_t one_shot             : 1;  /**< One-shot enable **/
  uint8_t                      : 1;  /**< RESERVED **/
  uint8_t swreset              : 1;  /**< Software reset. **/
  uint8_t i2c_dis              : 1;  /**< Disable I2C interface **/
  uint8_t if_add_inc           : 1;  /**< Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI). **/
  uint8_t stop_on_fth          : 1;  /**< Stop on FIFO watermark. Enable FIFO watermark level use **/
  uint8_t fifo_en              : 1;  /**< FIFO enable **/
  uint8_t boot                 : 1;  /**< Reboot memory content. **/
} lps22hb_ctrl_reg2_t;

typedef struct {
  uint8_t int_s                : 2;  /**< Data signal on INT_DRDY pin control bits **/
  uint8_t drdy                 : 1;  /**< Data-ready signal on INT_DRDY pin **/
  uint8_t f_ovr                : 1;  /**< FIFO overrun interrupt on INT_DRDY pin **/
  uint8_t f_fth                : 1;  /**< FIFO watermark status on INT_DRDY pin **/
  uint8_t f_fss5               : 1;  /**< FIFO full flag on INT_DRDY pin **/
  uint8_t pp_od                : 1;  /**< Push-pull/open drain selection on interrupt pads **/
  uint8_t int_h_l              : 1;  /**< Interrupt active-high/low. **/
} lps22hb_ctrl_reg3_t;

typedef struct {
  uint8_t wtm                  : 5;  /**< FIFO watermark level selection. **/
  uint8_t f_mode               : 3;  /**< FIFO mode selection **/
} lps22hb_fifo_ctrl_t;

typedef struct {
  uint8_t lc_en                : 1;  /**< Low current mode enable **/
  uint8_t                      : 1;  /**< RESERVED **/
  uint8_t                      : 6;  /**< RESERVED **/
} lps22hb_res_conf_t;

typedef struct {
  uint8_t ph                  : 1;  /**< Differential pressure High. **/
  uint8_t pl                  : 1;  /**< Differential pressure Low. **/
  uint8_t ia                  : 1;  /**< Interrupt active. **/
  uint8_t                     : 4;  /**< RESERVED **/
  uint8_t boot_status         : 1;  /**< If ‘1’ indicates that the Boot (Reboot) phase is running. **/
} lps22hb_int_source_t;

typedef struct {
  uint8_t fss                 : 6;  /**< FIFO stored data level **/
  uint8_t ovr                 : 1;  /**< FIFO overrun status **/
  uint8_t fth_fifo            : 1;  /**< FIFO watermark status **/
} lps22hb_fifo_status_t;

typedef struct {
  uint8_t p_da                : 1;  /**< Pressure data available **/
  uint8_t t_da                : 1;  /**< Temperature data available**/
  uint8_t                     : 2;  /**< RESERVED **/
  uint8_t p_or                : 1;  /**< Pressure data overrun. **/
  uint8_t t_or                : 1;  /**< Temperature data overrun **/
  uint8_t                     : 2;  /**< RESERVED **/
} lps22hb_status_t;

#endif /* LPS22HB_REG_H */












