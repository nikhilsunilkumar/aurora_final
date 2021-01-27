/*
 * datamanager.h
 *
 *  Created on: 11-Jan-2021
 *      Author: Daniya
 */

#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_
#include"aurora_pg_data_manager.h"
/*******************************************
 * Const and Macro Defines
 *******************************************/
#define BLOCKING_TIME_STATUS_Q 5U

/***********************************
 * Typedefs and Enum Declarations
 ***********************************/
enum status{
	SUCCESS,
	FAIL,
	COMPARE_FAIL,

};
enum direction{
	UP ='1',
	DOWN,
	UPDOWN,
	DOWNUP,

};
enum mode{
	MANUAL='1',
	AUTO,
};
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


void get_default_config(config_ascii_t*);

int update_config_struct(uint8_t ,uint8_t*);

int update_cmd_struct(uint8_t);

BaseType_t send_config_pg();

BaseType_t send_cmd_pg();

BaseType_t receive_status_pg(uint8_t*);

int reverse_direction();


#endif /* DATAMANAGER_H_ */
