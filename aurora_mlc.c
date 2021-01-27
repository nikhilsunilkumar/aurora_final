
/**
 * @file	aurora_mlc.c
 * @brief contains functions related to the Programmable Interrupt Timer
 *
 *
 *
 * @note
 *
 * Revision History:
 *		- 110121 MAP : Creation Date
 */


#include"aurora_mlc.h"

/*******"************************************
 * Const and Macro Defines
 *******************************************/
//none

/***********************************
 * Typedefs and Enum Declarations
 ***********************************/
// none

/***********************************
 * External Variable Declarations
 ***********************************/
config_ascii_t xconfig_ascii;
QueueHandle_t config_queue;
QueueHandle_t cmd_queue;
QueueHandle_t status_queue;

/***********************************
 * Const Declarations
 ***********************************/
// none

/***********************************
 * Public Variables
 ***********************************/
uint8_t state;
uint8_t is_master;

/***********************************
 * Private Variables
 ***********************************/
TaskHandle_t pg_task_handle,config_task_handle;

BaseType_t xHigherPriorityTaskWoken;
QueueHandle_t uart_queue;
QueueHandle_t cc_queue;

uint8_t uart_data_buff;
/***********************************
 * Private Prototypes
 ***********************************/
// none

/***********************************
 * Public Functions
 ***********************************/
//none


/**
 * @brief PIT ISR
 *
 *
 *
 *
 * @return 	void
 *
 * @note  This handler function will give a notification each time an interrupt occurs
 *
 * Revision History:
 * 	- 11 MAP: 	Creation Date
 */
void PIT0_IRQHandler(){

	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	xHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(pg_task_handle,	&xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	__DSB();
}



/**
 * @brief main function
 *
 * creates task
 *
 *
 *
 * @param
 * @return 	void
 *
 * @note  It is used to create a task
 *
 * Revision History:
 * 	- 110121 MAP: 	Creation Date
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	uart_init();

	config_queue 	= xQueueCreate(1,sizeof(config_ascii_t));
	cmd_queue		= xQueueCreate(1,sizeof(command_ascii_t));
	status_queue	= xQueueCreate(1,sizeof(status_ascii_t));
	uart_queue		= xQueueCreate(1,sizeof(uint8_t));


	//checking whether master or slave
	uint32_t result = init_i2c_tranfer();
	if (result == MASTER_CONFIGURED){
		is_master = 1;
	}
	else{
		is_master = 0;
	}
	//create config task
	if (xTaskCreate(config_task, "config_task", configMINIMAL_STACK_SIZE + 38, NULL, tskIDLE_PRIORITY + 3, &config_task_handle) != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	//create pattern generation task
	if (xTaskCreate(pattern_generation_task, "pg_task", configMINIMAL_STACK_SIZE + 38, NULL, tskIDLE_PRIORITY + 2, &pg_task_handle) != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}



	/* Start scheduling. */
	vTaskStartScheduler();
	for (;;)
		;
	return 0 ;


}


