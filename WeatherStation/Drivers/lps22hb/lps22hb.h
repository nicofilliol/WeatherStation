/*
 ******************************************************************************
 * @file    lps22hb.h
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb header: This file contains the memory-mapped register
 *                          struct, communication and test function prototypes
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
#ifndef LPS22HB_H
#define LPS22HB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lps22hb_reg.h"
#include "lps22hb_default.h"

/*! @defgroup lps22hb_I2C_defines Group: I2C defines   
*  lps22hb defines 
*  @{
*/

/* Read and write addresses */
#define LPS22HB_I2C_ADD_L 0x5CU /**< Pin 1 connected to GND **/
#define LPS22HB_I2C_ADD_H 0x5DU /**< Pin 1 connected to VDD **/
/* Device address  */
#define LPS22HB_I2C_ADD LPS22HB_I2C_ADD_L /* Default I2C address is low */

#define LPS22HB_I2C_ADD_READ LPS22HB_I2C_ADD << 1 + 1 /**< I2C Read address **/
#define LPS22HB_I2C_ADD_WRITE LPS22HB_I2C_ADD << 1   /**< I2C Write address **/

/*! @} */

/*! @defgroup lps22hb_error_codes Group: error codes   
*  lps22hb error codes
*  @{
*/

/* Error types */
typedef uint8_t lps22hb_err_t;
#define LPS22HB_SUCCESS         (lps22hb_err_t)(0)
#define LPS22HB_ERROR           (lps22hb_err_t)(1)
#define LPS22HB_ERR_CONFIG      (lps22hb_err_t)(1 << 1)
#define LPS22HB_ERR_RESPONSE    (lps22hb_err_t)(1 << 2)
#define LPS22HB_ERR_VALUE       (lps22hb_err_t)(1 << 3)
#define LPS22HB_NO_NEW_DATA     (lps22hb_err_t)(1 << 4)
#define LPS22HB_ERR_COMM        (lps22hb_err_t)(1 << 5)

/*! @} */

/* Device properties data  */
#define LPS22HB_WHO_AM_I_VAL (uint8_t)0xB1U /**< Device Who am I value **/

/* Bitmask */
#define LPS22HB_00_1F_READ_BITMASK 0x7F7B800  /**< read bitmask for bytes 0..31 **/
#define LPS22HB_00_1F_WRITE_BITMASK 0x7F73800 /**< write bitmask for bytes 0..31 **/

#define LPS22HB_20_3F_READ_BITMASK 0x81FE0  /**< read bitmask for bytes 32..63 **/
#define LPS22HB_20_3F_WRITE_BITMASK 0x00000000U /**< write bitmask for bytes 32..63 **/

#define LPS22HB_REG_SIZE 0x34U /**< number of registers of the LPS22HB sensor **/


#define LPS22HB_SCT_TO_P(STRUCT) (uint8_t *)&(STRUCT)
#define LPS22HB_SCT_TO_B(STRUCT) *LPS22HB_SCT_TO_P(STRUCT)
#define LPS22HB_SCT_REG_ADD(STRUCT, MEMBER_ADDRESS) LPS22HB_SCT_TO_P(STRUCT->reg) + MEMBER_ADDRESS
#define LPS22HB_NULL_PNT(PNT) PNT == 0

#define LPS22HB_CHECK_REG_SIZE_COMPILE_TIME(REG, SIZE) ((void)sizeof(char[1 - 2*(sizeof(REG) != SIZE)]))


/*! @defgroup lps22hb_reg_comm_struct Group: reg comm struct  
*  lps22hb register map and communication structs 
*  @{
*/
typedef struct
{
  uint8_t const reserved_0h_ah[11];                    /**< Ox00 - 0x0A **/
  lps22hb_interrupt_cfg_t interrupt_cfg;               /**< Ox0B **/
  uint8_t ths_p[2];                                    /**< Ox0C - 0x0D **/
  uint8_t const reserved_eh;                           /**< Ox0E **/
  uint8_t who_am_i;                                    /**< Ox0F **/
  lps22hb_ctrl_reg1_t ctrl_reg1;                       /**< Ox10 **/
  lps22hb_ctrl_reg2_t ctrl_reg2;                       /**< Ox11 **/
  lps22hb_ctrl_reg3_t ctrl_reg3;                       /**< Ox12 **/
  uint8_t const reserved_13h;                          /**< Ox13 **/
  lps22hb_fifo_ctrl_t fifo_ctrl;                       /**< Ox14 **/
  uint8_t ref_p[3];                                    /**< Ox15 - 0x17 **/
  uint8_t rpds[2];                                     /**< Ox18 - 0x19 **/
  lps22hb_res_conf_t res_conf;                         /**< Ox1A **/
  uint8_t const reserved_1bh_24h[10];                  /**< Ox1B - 0x24 **/
  lps22hb_int_source_t int_source;                     /**< Ox25 **/
  lps22hb_fifo_status_t fifo_status;                   /**< Ox26 **/
  lps22hb_status_t status;                             /**< Ox27 **/
  uint8_t press_out[3];                                /**< Ox28 - 0x2A **/
  uint8_t temp_out[2];                                 /**< Ox2B - 0x2C **/ 
  uint8_t const reserved_2dh_32h[6];                   /**< Ox2D - 0x32 **/
  uint8_t lpfp_res;                                    /**< Ox33 **/   
} lps22hb_registers_t;

typedef struct
{
  lps22hb_err_t (*write)(uint8_t reg, uint8_t *buf, uint8_t bytes); /**< User write function, should write multiple bytes **/
  lps22hb_err_t (*read)(uint8_t reg, uint8_t *buf, uint8_t bytes);  /**< User read function, should read multiple bytes **/
} lps22hb_communication_t;

typedef struct
{
  lps22hb_communication_t comm;
  lps22hb_registers_t reg;
} lps22hb_t;

/*! @} */

/*! @defgroup lps22hb_setup_functions Group: setup functions   
*  lps22hb functions
*  @{
*/

/*********** Functions declaration ***********/

/*********** Setup functions ***********/
/**
 * @brief Save the pointer of the user-defined write-read function.
 *        Checks the WHO_AM_I register and write/read. 
 * 
 * @warning If using 3-wire SPI set spi_mode variable to LPS22HB_3_WIRE_SPI.
 * @warning Make sure reg->ctrl3_c.if_inc is enabled if the MCU function used 
 *          assumes that the register address increases automatically.
 * 
 * @param configs           user defined setup struct (ptr)
 * @param spi_mode          set spi mode. Default: LPS22HB_4_WIRE_SPI
 * @return lps22hb_err_t    error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_setup_communication(lps22hb_t *const configs, lps22hb_sim_t spi_mode);

/**
 * @brief Write the user configurations in the lps22hb sensor, by iterating
 *        over all configuration registers
 * 
 * @param configs        user defined lps22hb_t struct (ptr)
 * @return lps22hb_err_t error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_setup(lps22hb_t *const configs);

/**
 * @brief Check that the user configuration stored in the chip is
 *        the same as the configuration stored in the user setup struct.
 * 
 * @param configs         user defined lps22hb_t struct (ptr)
 * @return lps22hb_err_t  error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_setup_check(lps22hb_t *const configs);

/**
 * @brief Check the WHO AM I register
 * 
 * @param configs        user defined lps22hb_t struct (ptr)
 * @return lps22hb_err_t error code, LPS22HB_SUCCESS on success
 */
lps22hb_err_t lps22hb_check_who_am_i(lps22hb_t *const configs);

/**
 * @brief Check if the master device is communicating correctly with the sensor, 
 *        by reading a register, writing it and then reading it and writing it again. 
 * 
 * @param configs          user defined lps22hb_t struct (ptr)
 * @return lps22hb_err_t   error code, LPS22HB_SUCCESS on success 
 */
lps22hb_err_t lps22hb_check_communication(lps22hb_t *const configs);

/*! @} */

/*! @defgroup lps22hb_communication_functions 
*  lps22hb functions
*  @{
*/

/*************** Communication fuctions ***************/

/**
 * @brief Read multiple registers starting from start_reg.
 * 
 * @param configs       user defined lps22hb_t struct (ptr)
 * @param data          buffer containing the read data. Must be at least as long as size
 * @param start_reg     address of first register to read, member of @ref lps22hb_registers
 * @param size          number of register addresses to read
 * @param update_config switch to enable the storage of the read data in the @ref configs register
 * @return lps22hb_err_t 
 */
lps22hb_err_t lps22hb_read_data(lps22hb_t *const configs, uint8_t *const data, uint8_t start_reg, uint8_t size, uint8_t update_config);


/**
  * @brief  Write multiple registers starting from start_reg.
  * 
  * @param configs        user defined lps22hb_t struct (ptr)
  * @param data           buffer containing the data to write to the sensor. Must be at least as long as size
  * @param start_reg      address of first register to read, member of @ref lps22hb_registers
  * @param size           number of register addresses to read
  * @param update_config  switch to enable the storage of the written data in the @ref configs_register
  * @return lps22hb_err_t error code, LPS22HB_SUCCESS on success
  */
lps22hb_err_t lps22hb_write_data(lps22hb_t *const configs, uint8_t *const data, uint8_t start_reg, uint8_t size, uint8_t update_config);


/**
  * @brief Register read command, read multiple registers from the sensor
  *        and store their value in the config->reg struct.
  *
  * @param configs      user defined lps22hb_t struct (ptr)
  * @param start_reg    address of first register to read, member of @ref lps22hb_registers 
  * @param size         number of register addresses to read
  * @return lps22hb_err_t error code, LPS22HB_SUCCESS on success
  */
lps22hb_err_t lps22hb_read_regs(lps22hb_t *const configs, uint8_t start_reg, uint8_t size);

/**
 * @brief Register read command, read a register from the sensor
 *        and store its value in the config->reg struct.
 * 
 * @param configs      user defined lps22hb_t struct (ptr)
 * @param reg          address of the register to read, member of @ref lps22hb_registers 
 * @return lps22hb_err_t 
 */
lps22hb_err_t lps22hb_read_reg(lps22hb_t *const configs, uint8_t reg);

/**
 * @brief Register write command, write multiple registers from the config struct to the
 *        sensor memory.
 * 
 * @param configs       user defined lps22hb_t struct (ptr)
 * @param start_reg     address of first register to write, member of @ref lps22hb_registers 
 * @param size          number of register addresses to read
 * @return lps22hb_err_t 
 */
lps22hb_err_t lps22hb_write_regs(lps22hb_t *const configs, uint8_t start_reg, uint8_t size);

/**
 * @brief Register write command, write a register from the config struct to the
 *        sensor memory.
 * 
 * @param configs       user defined lps22hb_t struct (ptr)
 * @param reg           address of first register to write, member of @ref lps22hb_registers 
 * @return lps22hb_err_t 
 */
lps22hb_err_t lps22hb_write_reg(lps22hb_t *const configs, uint8_t reg);

/*! @} */

#ifdef __cplusplus
}
#endif

#endif /* LPS22HB_H */
