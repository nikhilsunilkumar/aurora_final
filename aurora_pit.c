
/**
 * @file	aurora_pit.c
 * @brief contains functions related to the Programmable Interrupt Timer
 *
 *
 *
 * @note
 *
 * Revision History:
 *		- 110121 MAP : Creation Date
 */



#include "aurora_pit.h"

/*******************************************
 * Const and Macro Defines
 *******************************************/
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
/***********************************
 * Typedefs and Enum Declarations
 ***********************************/
//none

/***********************************
 * External Variable Declarations
 ***********************************/
// none

/***********************************
 * Const Declarations
 ***********************************/
// none

/***********************************
 * Public Variables
 ***********************************/


/***********************************
 * Private Variables
 ***********************************/
// none

/***********************************
 * Private Prototypes
 ***********************************/
// none

/***********************************
 * Public Functions
 ***********************************/



/**
 * @brief status_t set_pit_interval(config_hex_t *xconfig_hex)
 *
 *
 *
 * @param config_hex_t *xconfig_hex
 * @return 	 status_t
 *
 * @note  This function will set the PIT timer count according to the value of refresh rate and color code.
 *
 *
 * Revision History:
 * 	- 110121 MAP: 	Creation Date
 */

status_t set_pit_interval(config_hex_t *xconfig_hex){

	uint8_t color_code;
	uint8_t refresh_rate;
	uint32_t pit_ticktime=0;
	uint32_t pit_count=0;//timer count

	color_code = xconfig_hex->color_code;
	refresh_rate = xconfig_hex->refresh_rate;

	/*calculate the pit tick time ie., the time that is required for each pit interrupt*/
	pit_ticktime = (1000 * refresh_rate) / pow(2,color_code);

	pit_count = USEC_TO_COUNT(pit_ticktime, PIT_SOURCE_CLOCK);

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0,pit_count);
	return kStatus_Success;
}
/**
 * @brief enable_pit_interrupt
 *
 *
 *
 * @param  void
 * @return 	void
 *
 * @note  This function will enable the pit interrupt.
 *
 *
 * Revision History:
 * 	- 110121 MAP: 	Creation Date
 */

void enable_pit_interrupt(void){

	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	NVIC_SetPriority(PIT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY-1);

	EnableIRQ(PIT0_IRQn);

}

/**
 * @brief pit_init
 *
 *
 *
 * @param  void
 * @return 	void
 *
 * @note  This function will enable the pit interrupt.
 *
 *
 * Revision History:
 * 	- 110121 MAP: 	Creation Date
 */
void pit_init(void){

	pit_config_t pitConfig;
	PIT_GetDefaultConfig(&pitConfig);

	PIT_Init(PIT, &pitConfig);
}

/**
 * @brief  change_rate_delay
 *
 *
 *
 * @param  config_hex_t *xconfig_hex
 * @param command_ascii_t * xcommand_ascii
 * @param bool* global_state
 * @param uint32_t* pit_count_buffer
 *
 *
 * @return 	true/false
 *
 * @note  this function will give a nonblocking delay using pit timer
 *
 *The parameters used are refresh rate and change rate from the configuration.
 * It is used to  calculate the delay time for changing the color in between pattern change.
 * whenever it return true, it means it reached change rate
 * whenever it returns false,it means change rate did not happen
 *
 * Revision History:
 * 	- 130121 MAP: 	Creation Date
 * 	- 180121 : added state as a variable in order to facilitate pause continue
 * - 200121 : minor revision of the condition by which state is changed,
 * 				resetting pit_Count_buffer to pit_count-1
 * 	-220121 : changed the state variable and received it from outside. so that initialization is done once outside
 * 	-230121 : received the pit_count_buffer from outside. So initialization is done outside
 */

bool change_rate_delay(config_hex_t* xconfig_hex, command_ascii_t * xcommand_ascii, bool* global_state, uint32_t* pit_count_buffer){

	static uint32_t pit_ticktime = 0;/*it is the  time interval between two pit interrupts.*/
	static uint32_t pit_count = 0; /*it is the number of times a pit interrupt has to happen in order to match the change rate.*/
	//	static uint32_t pit_count_buffer = 0;



	if(xcommand_ascii->command == ' '){
		*global_state=!(*global_state);
		xcommand_ascii->command = DEFAULT_COMMAND;

	}

	/*pause and continue is implemented here.
	 * If space is pressed the state will be toggled and pattern will be stable while state is false*/

	pit_ticktime = (1000 * xconfig_hex->refresh_rate) / pow(2,xconfig_hex->color_code);

	pit_count = (1000*xconfig_hex->change_rate)/pit_ticktime;

	if(*global_state){

		*pit_count_buffer += 1 ;
	}

	if((*pit_count_buffer == pit_count)){

		*pit_count_buffer = 0;

		return true;
	}
	else{
		return false;
	}

}
