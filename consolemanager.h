/*
 * consolemanager.h
 *
 *
 * Revision History:
 *		- 110121 DA : Creation Date
  */
#ifndef CONSOLEMANAGER_H_
#define CONSOLEMANAGER_H_
#include "stdbool.h"
#include "MK64F12.h"
/*******************************************
 * Const and Macro Defines
 *******************************************/
#define UART UART0
#define UART_CLKSRC UART0_CLK_SRC
#define UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_IRQn UART0_RX_TX_IRQn
#define UART_IRQHandler UART0_RX_TX_IRQHandler

#define MIN_REFRESH_RATE 1U
#define MAX_REFRESH_RATE 99U
#define MIN_CYCLE 0U
#define MAX_CYCLE 99U
#define MIN_CHANGE_RATE 1U
#define MAX_CHANGE_RATE 999U
/***********************************
 * Typedefs and Enum Declarations
 ***********************************/
typedef enum _parameter_id
{
	START_COLOR_ID,
	END_COLOR_ID,
	STEP_SIZE_ID,
	MODE_ID,
	DIRECTION_ID,
	REFRESH_RATE_ID,
	CYCLES_ID,
	CHANGE_RATE_ID,
}param_t;


/***********************************
 * Const Declarations
 ***********************************/
// none

/***********************************
 * Variable Declarations
 ***********************************/
// none

/***********************************
 * Prototypes
 ***********************************/

void uart_init(void);

void enable_uart_isr();

/*!
 * @brief Enables or disables the UART MSBF.
 *
 * This function used to make ensure that
 * LSB (bit0) is the first bit that is
 * transmitted following the start bit,
 * i,e disables MSBF( most significant bit first). .
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void uart_msbf(UART_Type *base, bool enable)
{
    if (enable)
    {
        base->S2 |= UART_S2_MSBF_MASK;
    }
    else
    {
        base->S2 &= ~UART_S2_MSBF_MASK;
    }
}


int get_keyinput();

int get_keyinput_nonblocking();

void uart_slave_enable();

int create_uartqueue();

void print_message(char *);

void print_data(uint8_t * data,uint8_t);

int validate_buffer(uint8_t , uint8_t*);

int validate_byte(uint8_t, uint8_t , uint8_t);

int validate_executionkey(uint8_t);

int compare(uint8_t*, uint8_t*);


#endif /* CONSOLEMANAGER_H_ */
