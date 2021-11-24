/* helper_functions.c
 *
 *  Created on: 23 Mar 2020
 *      Author: Federico Villani
 */

#include "helper_functions.h"
/**
 * external variables and defines
 */
extern UART_HandleTypeDef huart1;
volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
#define UART_HANDLE huart1

// #define USE_ITM
/**
 * Transmission and reception macros
 */
/**
 *
 * @param ch
 */
static void transmit_char_serial(char ch);
static char receive_char_serial(void);
static void transmit_char_ITM(char ch);
static char receive_char_ITM(void);

/**
 * @brief PUTCHAR_PROTOTYPE function, called from printf
 * @param ch 	: Char to be written to console
 * @return
 */
PUTCHAR_PROTOTYPE {
#ifdef USE_ITM
	transmit_char_ITM((char) ch);
#else
    transmit_char_serial((char) ch);
#endif
    return 0;
}
/**
 * @brief GETCHAR_PROTOTYPE function, called from scanf
 * @return read out character
 */
GETCHAR_PROTOTYPE {
    char ch;
#ifdef USE_ITM
	ch = receive_char_ITM();
	transmit_char_ITM(ch);
#else
    ch = receive_char_serial();
    transmit_char_serial(ch);
#endif
    return (int) ch;
}

static void transmit_char_serial(char ch) {
    HAL_UART_Transmit(&UART_HANDLE, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
}
static char receive_char_serial() {
    char ch;
    HAL_UART_Receive(&UART_HANDLE, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
    return ch;
}
static void transmit_char_ITM(char ch) {
	ITM_SendChar((uint32_t)ch);
}
static char receive_char_ITM() {
    char ch = 0;
    ch = ITM_ReceiveChar();
    return ch;
}

