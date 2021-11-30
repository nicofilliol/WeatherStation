/*
 ******************************************************************************
 * @file    lps22hb.c 
 * @author  Universal Driver Development Team - Jacopo Graldi
 * @brief   lps22hb driver file
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

/*************** Includes ***************/
#include "lps22hb.h"

/*************** Static variables ***************/
static lps22hb_communication_t *lps22hb_comm;
static uint32_t lps22hb_writable_regs[2] = {LPS22HB_00_1F_WRITE_BITMASK,
                                            LPS22HB_20_3F_WRITE_BITMASK};
static uint32_t lps22hb_readable_regs[2] = {LPS22HB_00_1F_READ_BITMASK,
                                            LPS22HB_20_3F_READ_BITMASK};

/*************** Static fuctions ***************/
static inline lps22hb_err_t check_struct_pointer(lps22hb_t *const configs)
{
    return configs == 0 ||
           (configs->comm.write) == 0 ||
           (configs->comm.read) == 0 ||
           &(configs->reg) == 0;
}

static inline lps22hb_err_t lps_memcmp(const void *mem1, const void *mem2, uint32_t len)
{
    if (LPS22HB_NULL_PNT(mem1) || LPS22HB_NULL_PNT(mem2))
        return LPS22HB_ERROR;
    uint8_t *m1 = (uint8_t *)mem1;
    uint8_t *m2 = (uint8_t *)mem2;
    if (m1 == m2 || !len)
        return 0;
    for (; 0 < len; --len, ++m1, ++m2)
    {
        if (*m1 != *m2)
            return LPS22HB_ERR_VALUE;
    }
    return LPS22HB_SUCCESS;
}
static inline lps22hb_err_t lps_memcpy(void *const dst, const void *src, uint32_t len)
{
    if (LPS22HB_NULL_PNT(dst) || LPS22HB_NULL_PNT(src))
        return LPS22HB_ERROR;
    uint8_t *d = (uint8_t *)dst;
    uint8_t *s = (uint8_t *)src;
    if (d == s || !len)
        return LPS22HB_SUCCESS;
    for (; 0 < len; --len, ++d, ++s)
    {
        *d = *s;
    }
    return LPS22HB_SUCCESS;
}

static inline uint8_t lps22hb_reg_get_writable_block(uint8_t start_reg)
{
    uint8_t size = 0;
    while (start_reg < LPS22HB_REG_SIZE)
    {
        /* Checks if the bit corresponding to the register address is not set */
        if (!(lps22hb_writable_regs[start_reg / 32] & (1 << (start_reg % 32))))
            return size;
        ++size;
        ++start_reg;
    }
    return size;
}

static lps22hb_err_t lps22hb_reg_check_writable(uint8_t start_reg, uint8_t size)
{
    if (size + start_reg > LPS22HB_REG_SIZE)
        return LPS22HB_ERROR;
    while (size)
    {
        /* Checks if the bit corresponding to the register address is not set */
        if (!(lps22hb_writable_regs[start_reg / 32] & (1 << (start_reg % 32))))
            return LPS22HB_ERROR;
        --size;
    }
    return LPS22HB_SUCCESS;
}

static lps22hb_err_t lps22hb_reg_check_readable(uint8_t start_reg, uint8_t size)
{
    if (size + start_reg > LPS22HB_REG_SIZE)
        return LPS22HB_ERROR;
    while (size)
    {
        /* Checks if the bit corresponding to the register address is not set */
        if (!(lps22hb_readable_regs[start_reg / 32] & (1 << (start_reg % 32))))
            return LPS22HB_ERROR;
        --size;
        ++start_reg;
    }
    return LPS22HB_SUCCESS;
}

static lps22hb_err_t lps22hb_update_conf_reg(lps22hb_t *const configs, uint8_t *src, uint8_t start_reg, uint8_t size)
{
    if ((lps22hb_reg_check_writable(start_reg, size) &&
         lps22hb_reg_check_readable(start_reg, size)) ||
        check_struct_pointer(configs))
        return LPS22HB_ERROR;
    return lps_memcpy(((void *)&configs->reg) + start_reg, src, size);
}

/*************** Setup fuctions ***************/
lps22hb_err_t lps22hb_setup_communication(lps22hb_t *const configs, lps22hb_sim_t spi_mode)
{
    /* check size of lps22hb register struct at compile time  */
    LPS22HB_CHECK_REG_SIZE_COMPILE_TIME(lps22hb_registers_t, LPS22HB_REG_SIZE);

    if (check_struct_pointer(configs))
        return LPS22HB_ERR_CONFIG;

    /* Save pointer to function locally (needed for forward compatibility of interrupts) */
    lps22hb_comm = &(configs->comm);

    lps22hb_err_t err = LPS22HB_SUCCESS;

    /* set spi mode and apply modifications */
    configs->reg.ctrl_reg1.sim = spi_mode;
    err |= lps22hb_write_reg(configs, LPS22HB_CTRL_REG1);
    err |= lps22hb_check_communication(configs);
    return err;
}

lps22hb_err_t lps22hb_setup(lps22hb_t *const configs)
{
    lps22hb_err_t err = LPS22HB_SUCCESS;

    if (check_struct_pointer(configs))
        return LPS22HB_ERR_CONFIG;

    uint8_t register_add = 0;
    while (register_add < LPS22HB_REG_SIZE)
    {
        uint8_t writable_block = lps22hb_reg_get_writable_block(register_add);
        err |= lps22hb_write_regs(configs, register_add, writable_block);
        register_add += writable_block + 1;
    }
    return err;
}

lps22hb_err_t lps22hb_setup_check(lps22hb_t *const configs)
{
    lps22hb_err_t err = LPS22HB_SUCCESS;
    lps22hb_registers_t buff_regs;
    if (check_struct_pointer(configs))
        return LPS22HB_ERR_CONFIG;

    uint8_t register_add = 0;
    while (register_add < LPS22HB_REG_SIZE)
    {
        uint8_t writable_block = lps22hb_reg_get_writable_block(register_add);
        err |= lps22hb_read_data(configs, LPS22HB_SCT_TO_P(buff_regs), register_add, writable_block, 0);
        register_add += writable_block + 1;
    }
    err |= lps_memcmp(LPS22HB_SCT_TO_P(configs->reg), LPS22HB_SCT_TO_P(buff_regs), LPS22HB_REG_SIZE - 1);
    return err;
}

lps22hb_err_t lps22hb_check_who_am_i(lps22hb_t *const configs)
{
    if (check_struct_pointer(configs))
        return LPS22HB_ERR_CONFIG;
    uint8_t who_am_i_response;
    lps22hb_read_data(configs, &who_am_i_response, LPS22HB_WHO_AM_I, 1, 0);
    if (LPS22HB_WHO_AM_I_VAL == who_am_i_response)
        return LPS22HB_SUCCESS;
    else
        return LPS22HB_ERR_RESPONSE;
}

lps22hb_err_t lps22hb_check_communication(lps22hb_t *const configs)
{
    uint8_t buffer[2];
    uint8_t cmp[2];
    lps22hb_err_t err = LPS22HB_SUCCESS;

    uint8_t rpds_l_test  =  0xAA;
    uint8_t rpds_h_test  =  0x55;
    buffer[0] = LPS22HB_SCT_TO_B(rpds_l_test);
    buffer[1] = LPS22HB_SCT_TO_B(rpds_h_test);

    /* Check correct reading of registers, then read, write and read back */
    if (lps22hb_check_who_am_i(configs))
        return LPS22HB_ERR_RESPONSE;

    err |= lps22hb_read_regs(configs, LPS22HB_RPDS_L, 2);
    err |= lps22hb_write_data(configs, buffer, LPS22HB_RPDS_L, 2, 0);
    err |= lps22hb_read_data(configs, cmp, LPS22HB_RPDS_L, 2, 0);
    err |= lps_memcmp(buffer, cmp, 2);
    err |= lps22hb_write_regs(configs, LPS22HB_RPDS_L, 2);

    return err;
}

/*************** Communication fuctions ***************/
lps22hb_err_t lps22hb_read_data(lps22hb_t *const configs, uint8_t *data, uint8_t start_reg, uint8_t size, uint8_t upd_config)
{
    if (check_struct_pointer(configs) || lps22hb_reg_check_readable(start_reg, size))
        return LPS22HB_ERR_CONFIG;
    lps22hb_err_t err = LPS22HB_SUCCESS;

    configs->comm.read(start_reg, data, size);
    if (upd_config)
        err |= lps22hb_update_conf_reg(configs, data, start_reg, size);
    return err;
}

lps22hb_err_t lps22hb_write_data(lps22hb_t *const configs, uint8_t *data, uint8_t start_reg, uint8_t size, uint8_t update_config)
{
    if (check_struct_pointer(configs) || lps22hb_reg_check_writable(start_reg, size))
        return LPS22HB_ERR_CONFIG;
    lps22hb_err_t err = LPS22HB_SUCCESS;

    configs->comm.write(start_reg, data, size);
    if (update_config)
        err |= lps22hb_update_conf_reg(configs, data, start_reg, size);
    return err;
}

lps22hb_err_t lps22hb_read_regs(lps22hb_t *const configs, uint8_t start_reg, uint8_t size)
{
    return lps22hb_read_data(configs, LPS22HB_SCT_REG_ADD(configs, start_reg), start_reg, size, 0);
}

lps22hb_err_t lps22hb_write_regs(lps22hb_t *const configs, uint8_t start_reg, uint8_t size)
{
    //since data is already in configs, do not care about writing it in
    return lps22hb_write_data(configs, LPS22HB_SCT_REG_ADD(configs, start_reg), start_reg, size, 0);
}

lps22hb_err_t lps22hb_write_reg(lps22hb_t *const configs, uint8_t reg)
{
    return lps22hb_write_regs(configs, reg, 1);
}

lps22hb_err_t lps22hb_read_reg(lps22hb_t *configs, uint8_t reg)
{
    return lps22hb_read_regs(configs, reg, 1);
}

