
/*
 * StateMachine.h
 *
 *  Created on: 12-Jan-2021
 *      Author: meera
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "aurora_pg_data_manager.h"
#include <consolemanager.h>
#include "datamanager.h"
#include "ctype.h"
#include "aurora_i2c.h"
#include "aurora_pat_gen.h"
/*******************************************
 * Const and Macro Defines
 *******************************************/
#define MAIN_HEADING	"\n\n\r################################################################################\n\r\n\r\t\t\t\tAURORA\n\r\n\r################################################################################\n\r"
#define CURR_CONFIG		"\n\n\r********************************************************************************\n\r\t\t\tCURRENT CONFIGURATION\n\r********************************************************************************\n\r"
#define SYS_CONFIG		"\n\n\r********************************************************************************\n\r\t\t\tSYSTEM CONFIGURATION\n\r********************************************************************************\n\r"
#define PAT_CONFIG		"\n\n\r********************************************************************************\n\r\t\t\tPATTERN CONFIGURATION\n\r********************************************************************************\n\r"
#define COLOUR_CONFIG	"\n\n\r********************************************************************************\n\r\t\t\tColour Configuration\n\r********************************************************************************\n\r"
#define MODE_CONFIG		"\n\n\r********************************************************************************\n\r\t\t\tMode Configuration\n\r********************************************************************************\n\r"
#define DIR_CONFIG		"\n\n\r********************************************************************************\n\r\t\t\tDirection Configuration\n\r********************************************************************************\n\r"
#define DEV_STATUS	"\n\r\tDEVICE STATUS\t\t:\t"
#define COMP_STATUS	"\r\tCOMPANION STATUS\t:\t"
#define REFRESH_RATE	"\n\r\tREFRESH RATE (in ms)\t:\t"
#define COLOUR_CODING	"\n\r\tCOLOUR CODING\t\t:\t"
#define START_COLOUR	"\r\n\n\tSTART_COLOUR\t\t:\t"
#define END_COLOUR	"\n\r\tEND_COLOUR\t\t:\t"
#define STEP_SIZE	"\n\r\tSTEP_SIZE\t\t:\t"
#define MODE	"\n\n\r\tMODE\t\t\t:\t"
#define CYCLE	"\n\r\tCYCLE\t\t\t:\t"
#define DIRECTION	"\n\r\tDIRECTION\t\t:\t"
#define CHANGE_RATE	"\n\r\tCHANGE RATE (in 10ms)\t:\t"
#define PROMPT_HS		"\n\n\rPRESS KEY\n\r\t[S] : System Configuration\t[P] : Pattern Configuration\t[X] : Execution\n\n"
#define PROMPT_PS		"\n\r\t[C] :\tColor Configurations\n\r\t[M] :\tMode Configurations\n\r\t[D] :\tDirection Configurations\n\r\t[Q] :\tGo back to Home Screen\n\n\rChoose option\t: "
#define PROMPT_MS		"\n\n\rPlease select one of the following mode :\n\n\r\t1. Manual\n\r\t2. Automatic\n"
#define PROMPT_DS		"\n\n\rTo change the direction select from below :\n\n\r\t1. Up\n\r\t2. Down\n\r\t3. Up-Down\n"
#define QUIT		"\n\n\r\t[Q] :\tGo back to Home screen"
#define BACK		"\n\r\t[B] :\tSkip and Go back to Previous Menu\n\r"
#define COLOUR_STATUS	"\rCurrent LED Color Code\t: "
#define CYCLE_STATUS	"\t\tCycles Left\t: "
#define MANUAL_KEYS		"\n\n\r********************************************************************************\n\n\r[>] : To the next LED pattern\t[<] : To the previous LED pattern\t[Q]: Stop\n\n\r********************************************************************************\r\n\n"
#define AUTO_KEYS		"\n\n\r********************************************************************************\n\n\r[SPACE BAR] : Pause/Resume\t[Q] : Stop\n\n\r********************************************************************************\r\n\n"

#define ERROR_MSG	"\n\rInvalid Input\n\r"

#define SLAVE_CONNECTED 1U
#define SLAVE_NOT_CONNECTED 0U;
#define MAX_SIZE_REFRESH 3U

/*******************************************************************************
* Typedefs and Enum Declarations
 ******************************************************************************/
enum screen{
	HOMESCREEN,
	SYSTEMCONFIG_SCREEN,
	PATTERNCONFIG_SCREEN,
	EXECUTION_SCREEN
};

/***********************************
 * Variable Declarations
 ***********************************/
// none

/***********************************
 * Prototypes
 ***********************************/

int homescreen_func();
void display_config();
int systemconfig_func();
int patternconfig_func();
int colour_config();
int mode_config();
int direction_config();
int execution_func();
void config_task(void *pvParameters);

#endif /* STATEMACHINE_H_ */
