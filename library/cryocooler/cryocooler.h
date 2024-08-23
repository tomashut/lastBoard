/*
 * cryocooler.h
 *
 *  Created on: May 13, 2024
 *      Author: CRINSURANCE 1
 */

#ifndef CRYOCOOLER_CRYOCOOLER_H_
#define CRYOCOOLER_CRYOCOOLER_H_

/***********************************************************************
 *							INCLUDES
 ***********************************************************************/
#include "hardwareConfig.h"
#include "typdef_basicLib.h"
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "digital_outputs_config.h"
#include "uart_config.h"
//#include "systemTime.h"
#endif
/***********************************************************************
 *							MACROS
 ***********************************************************************/

/* Cold Tip Temperature ---------------------------------------------------*/

/**
 * @brief  Displays the cold-tip temperature via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_COLD_TIP_TEMPERATURE()\
		do {							  \
			char command[30];			  \
			sprintf(command, "TC");	  \
			send_uart_command(command);   \
		} while (0)

/* Control Mode -----------------------------------------------------------*/
/**
 * @brief  Use the command to change the control mode that’s currently being used.
 * @param  value specifies the PID mode value.
 *         + value = 0 -> Power control mode
 *         + value = 2 -> Temperature control mode
 * @retval None
 */
#define SET_CONTROL_MODE(value)            				\
		do {                                   			\
			char command[30];                  			\
			sprintf(command, "SET PID=%d", value);	\
			send_uart_command(command);        			\
		} while (0)

/**
 * @brief  Displays the current control mode via UART.
 * A return of 000.00 indicates that power control mode is currently in use.
 * A return of 002.00 indicates that temperature control mode is currently in use.
 * @param  None
 * @retval None
 */
#define DISPLAY_CURRENT_CONTROL_MODE()     \
		do {                                   \
			char command[30];                  \
			sprintf(command, "SET PID");   \
			send_uart_command(command);        \
		} while (0)

/**
 * @brief   Save the control mode that is currently in use as the new default control mode via UART.
 * A return of 000.00 indicates that power control mode has been saved as the default control mode.
 * A return of 002.00 indicates that temperature control mode has been saved as the default control mode
 * @param  None
 * @retval None
 */
#define CHANGE_DEFAULT_CONTROL_MODE()      \
		do {                                   \
			char command[30];                  \
			sprintf(command, "SAVE PID");  \
			send_uart_command(command);        \
		} while (0)

/* Configured Cryocooler Type ---------------------------------------------*/

/**
 * @brief  Displays the configured cryocooler type via UART.
 * MODE:
 *     + 000.00 – Sunpower reserved mode
 *     + 001.00 – CryoTel CT
 *     + 002.00 – CryoTel GT
 *     + 003.00 – CryoTel MT
 *
 * @param  None
 * @retval None
 */
#define DISPLAY_CONFIGURED_CRYOCOOLER_TYPE() \
		do {                                     \
			char command[30];                    \
			sprintf(command, "MODE");        \
			send_uart_command(command);          \
		} while (0)

/* Controller Code Version ------------------------------------------------*/

/**
 * @brief  Displays the controller code version via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_CONTROLLER_CODE_VERSION() \
		do {                                  \
			char command[30];                 \
			sprintf(command, "VERSION");  \
			send_uart_command(command);       \
		} while (0)

/* Controller Serial Number -----------------------------------------------*/

/**
 * @brief  Display the controller’s serial number in addition to the drawing
 * 		number and revision level of the controller’s circuit board,
 * 		and the	version number of the installed software code.
 * @param  None
 * @retval None
 */
#define DISPLAY_CONTROLLER_SERIAL_NUMBER()\
		do {                                  \
			char command[30];                 \
			sprintf(command, "SERIAL");   \
			send_uart_command(command);       \
		} while (0)

/* Controller Parameters --------------------------------------------------*/

/**
 * @brief  Resets the controller parameters to factory defaults via UART.
 * @param  None
 * @retval None
 */
#define RESET_CONTROLLER_PARAMETERS_TO_FACTORY_DEFAULTS()  \
		do {                                                   \
			char command[30];                                  \
			sprintf(command, "RESET=F");                   \
			send_uart_command(command);                        \
		} while (0)

/* Cooler Power as Measured by Controller ---------------------------------*/

/**
 * @brief  Displays the cooler power as measured by the controller via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER() \
		do {                                              \
			char command[30];                             \
			sprintf(command, "P");                    \
			send_uart_command(command);                   \
		} while (0)

/* Current Commanded Power & Power Limits ---------------------------------*/

/**
 * @brief  Displays the current commanded power and power limits via UART.
 * 		The computer displays:	E
 * 								maximum allowable power output [Watts]
 * 								minimum allowable power output [Watts]
 * 								current commanded power [Watts]
 * @param  None
 * @retval None
 */
#define DISPLAY_CURRENT_POWER_AND_LIMITS() \
		do {                                   \
			char command[30];                  \
			sprintf(command, "E");         \
			send_uart_command(command);        \
		} while (0)

/* Error Code -------------------------------------------------------------*/

/**
 * @brief  Displays the error code via UART.
 * 		An error code is a six-digit binary number that identifies which, if any, errors are occurring.
 * 		|---------------|-------------------------------|
 * 		|	Error Code	|	Name of the Error Indicated	|
 * 		|---------------|-------------------------------|
 * 		|	000001 		|	Over Current				|
 * 		|	000010		|	Jumper Error				|
 * 		|	000100		|	Serial Communication Error	|
 * 		|	001000 		|	Non-Volatile Memory Error	|
 * 		|	010000 		|	Watchdog Error				|
 * 		|	100000 		|	Temperature Sensor Error	|
 * 		|---------------|-------------------------------|
 * @param  None
 * @retval None
 */
#define DISPLAY_ERROR_CODE()        \
		do {                            \
			char command[30];           \
			sprintf(command, "ERROR"); \
			send_uart_command(command); \
		} while (0)

/* Operating State --------------------------------------------------------*/

/**
 * @brief  Displays the operating state via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_OPERATING_STATE()    \
		do {                             \
			char command[30];            \
			sprintf(command, "STATE"); \
			send_uart_command(command);  \
		} while (0)

/* Integral Constant of Temperature Control Loop --------------------------*/

/**
 * @brief  Sets the integral constant of the temperature control loop via UART.
 * @param  value Specifies the value of the integral constant.
 * @retval None
 */
#define SET_INTEGRAL_CONSTANT_OF_TEMP_CONTROL_LOOP(value) \
		do {                                              \
			char command[30];                                 \
			sprintf(command, "SET KI=%.5f", value);         \
			send_uart_command(command);                       \
		} while (0)

/**
 * @brief  Displays the integral constant of the temperature control loop via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_INTEGRAL_CONSTANT_OF_TEMP_CONTROL_LOOP() \
		do {                                             \
			char command[30];                            \
			sprintf(command, "SET KI");              \
			send_uart_command(command);                  \
		} while (0)

/* Proportional Constant of Temperature Control Loop ----------------------*/

/**
 * @brief  Sets the proportional constant of the temperature control loop via UART.
 * @param  value Specifies the value of the proportional constant.
 * @retval None
 */
#define SET_PROPORTIONAL_CONSTANT_OF_TEMP_CONTROL_LOOP(value) \
		do {                                                  \
			char command[30];                                 \
			sprintf(command, "SET KP=%.5f", value);       \
			send_uart_command(command);                       \
		} while (0)

/**
 * @brief  Displays the proportional constant of the temperature control loop via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_PROPORTIONAL_CONSTANT_OF_TEMP_CONTROL_LOOP() \
		do {                                                 \
			char command[30];                                \
			sprintf(command, "SET KP");                  \
			send_uart_command(command);                      \
		} while (0)

/* Soft-Stop Control Mode -------------------------------------------------*/

/**
 * @brief  Sets the soft stop control mode via UART.
 * 		   + Entering a value of 0 (mode 0) allows the soft-stop function to be
 * 		   enabled or disabled using only the SET SSTOP=<Value> command.
 * 		   + Entering a value of 1 (mode 1) allows the soft-stop function to be
 * 		   enabled or disabled using only Digital Input 1.
 * @param  value Specifies the value of the soft stop control mode.
 * @retval None
 */
#define SET_SOFT_STOP_CONTROL_MODE(value)            	 \
		do {                                             \
			char command[30];                            \
			sprintf(command, "SET SSTOPM=%d", value);\
			send_uart_command(command);                  \
		} while (0)

/**
 * @brief Displays the soft-stop control mode via UART.
 *		  A return of 000.00 (mode 0) indicates that only the SET SSTOP=<Value>
 *		  command can be used to enable or disable the soft-stop function.
 *		  A return of 001.00 (mode 1) indicates that only Digital Input 1
 *		  (pin 5 on the controller’s I/O connector) can be used to enable or disable the soft-stop function.
 * @param  None
 * @retval None
 */
#define DISPLAY_SOFT_STOP_CONTROL_MODE()   	   \
		do {                                   \
			char command[30];                  \
			sprintf(command, "SET SSTOPM");\
			send_uart_command(command);        \
		} while (0)

/* Soft-Stop State --------------------------------------------------------*/

/**
 * @brief  Sets the soft stop state via UART.
 * 		   + Entering a value of 0 restarts a stopped cryocooler and
 * 		   disables the soft-stop function.
 * 		   + Entering a value of 1 begins a soft stop of the cryocooler
 * 		   and enables the soft-stop function
 * @param  value Specifies the value of the soft stop state.
 * @retval None
 */
#define SET_SOFT_STOP_STATE(value)                 		\
		do {                                            \
			char command[30];                           \
			sprintf(command, "SET SSTOP=%d", value);\
			send_uart_command(command);                 \
		} while (0)

/**
 * @brief  Displays the soft-stop state via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_SOFT_STOP_STATE()         \
		do {                                  \
			char command[30];                 \
			sprintf(command, "SET SSTOP");\
			send_uart_command(command);       \
		} while (0)

/* Target Power Output ----------------------------------------------------*/

/**
 * @brief  Sets the target power output via UART.
 * @param  value Specifies the value of the target power output.
 * @retval None
 */
#define SET_TARGET_POWER_OUTPUT(value)                	  \
		do {                                              \
			char command[30];                             \
			sprintf(command, "SET PWOUT=%d", value);\
			send_uart_command(command);                   \
		} while (0)

/**
 * @brief  Displays the target power output via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_TARGET_POWER_OUTPUT()         \
		do {                                  \
			char command[30];                 \
			sprintf(command, "SET PWOUT");\
			send_uart_command(command);       \
		} while (0)

/* Target Temperature -----------------------------------------------------*/

/**
 * @brief  Sets the target temperature via UART.
 * @param  value Specifies the value of the target temperature.
 * @retval None
 */
#define SET_TARGET_TEMPERATURE(value)                   	\
		do {                                                \
			char command[30];                               \
			sprintf(command, "SET TTARGET=%.3f", value);\
			send_uart_command(command);                     \
		} while (0)

/**
 * @brief  Displays the target temperature via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_TARGET_TEMPERATURE()          	\
		do {                                    \
			char command[30];                   \
			sprintf(command, "SET TTARGET");\
			send_uart_command(command);         \
		} while (0)

/* Temperature Band -------------------------------------------------------*/

/**
 * @brief  Sets the temperature band via UART.
 * @param  value Specifies the value of the temperature band.
 * @retval None
 */
#define SET_TEMPERATURE_BAND(value)                		  \
		do {                                           	  \
			char command[30];                          	  \
			sprintf(command, "SET TBAND=%.3f", value);\
			send_uart_command(command);                	  \
		} while (0)

/**
 * @brief  Displays the temperature band via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_TEMPERATURE_BAND()         	  \
		do {                                  \
			char command[30];                 \
			sprintf(command, "SET TBAND");\
			send_uart_command(command);       \
		} while (0)

/* Thermostat Mode --------------------------------------------------------*/

/**
 * @brief  Sets the thermostat mode via UART.
 * 		+ value = 0 -> disables the controller’s ability to work with a thermostat.
 * 		+ value = 1 -> enables the controller’s ability to work with a thermostat.
 * @param  value Specifies the value of the thermostat mode.
 * @retval None
 */
#define SET_THERMOSTAT_MODE(value)                  	 \
		do {                                             \
			char command[30];                            \
			sprintf(command, "SET TSTATM=%d", value);\
			send_uart_command(command);               	 \
		} while (0)

/**
 * @brief  Displays the thermostat mode via UART.
 * 		A return of 000.00 indicates that use of a thermostat is disabled.
 * 		A return of 001.00 indicates that use of a thermostat is enabled.
 * @param  None
 * @retval None
 */
#define DISPLAY_THERMOSTAT_MODE()              \
		do {                                   \
			char command[30];                  \
			sprintf(command, "SET TSTATM");\
			send_uart_command(command);        \
		} while (0)

/* Thermostat State -------------------------------------------------------*/

/**
 * @brief  Displays the thermostat state via UART.
 * 		The thermostat state indicates the current state (open or closed) of a thermostat
 * 		connected across pin 7 and pin 10 or 12 of the controller’s I/O connector.
 * 		-> A return of 000.00 indicates that the thermostat is open.
 * 		-> A return of 001.00 indicates that the thermostat is closed.
 * @param  None
 * @retval None
 */
#define DISPLAY_THERMOSTAT_STATE()        \
		do {                              \
			char command[30];             \
			sprintf(command, "TSTAT");\
			send_uart_command(command);   \
		} while (0)

/* User-Defined Minimum Power Output ---------------------------------------*/

/**
 * @brief  Sets the user-defined minimum power output via UART.
 * @param  value Specifies the value of the user-defined minimum power output.
 * @retval None
 */
#define SET_USER_DEFINED_MINIMUM_POWER_OUTPUT(value) 	\
		do {                                            \
			char command[30];                           \
			sprintf(command, "SET MIN=%.3f", value);\
			send_uart_command(command);                 \
		} while (0)

/**
 * @brief  Displays the user-defined minimum power output via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_USER_DEFINED_MINIMUM_POWER_OUTPUT() \
		do {                                        \
			char command[30];                       \
			sprintf(command, "SET MIN");        \
			send_uart_command(command);             \
		} while (0)

/* User-Defined Maximum Power Output ---------------------------------------*/

/**
 * @brief  Sets the user-defined maximum power output via UART.
 * @param  value Specifies the value of the user-defined maximum power output.
 * @retval None
 */
#define SET_USER_DEFINED_MAXIMUM_POWER_OUTPUT(value) 	\
		do {                                            \
			char command[30];                           \
			sprintf(command, "SET MAX=%.3f", value);\
			send_uart_command(command);                 \
		} while (0)

/**
 * @brief  Displays the user-defined maximum power output via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_USER_DEFINED_MAXIMUM_POWER_OUTPUT() \
		do {                                        \
			char command[30];                       \
			sprintf(command, "SET MAX");        \
			send_uart_command(command);             \
		} while (0)

/* Display User-Defined Minimum & Maximum Power Output ----------------------*/

/**
 * @brief  Displays the user-defined minimum and maximum power output via UART.
 * @param  None
 * @retval None
 */
#define DISPLAY_USER_DEFINED_MINIMUM_AND_MAXIMUM_POWER_OUTPUT() \
		do {                                                    \
			char command[30];                                   \
			sprintf(command, "SHOW MX");                    \
			send_uart_command(command);                         \
		} while (0)

/* Lock User-Lockable Commands ---------------------------------------------*/

/**
 * @brief  Locks user-lockable commands via UART.
 * 		A return of 001.00 confirms that the group of lockable-commands is locked
 * 		and that the parameters associated with those commands cannot be changed
 * @param  password Specifies the password for locking.
 * @retval None
 */
#define LOCK_USER_LOCKABLE_COMMANDS(password)     	  \
		do {                                          \
			char command[30];                         \
			sprintf(command, "LOCK=%s", password);\
			send_uart_command(command);               \
		} while (0)

/**
 * @brief  Unlocks user-lockable commands via UART.
 * 		-> A return of 000.00 confirms that the commands are unlocked
 * @param  password Specifies the password for unlocking.
 * @retval None
 */
#define UNLOCK_USER_LOCKABLE_COMMANDS(password)     	\
		do {                                            \
			char command[30];                           \
			sprintf(command, "UNLOCK=%s", password);\
			send_uart_command(command);                 \
		} while (0)

/**
 * @brief  Change the user password via UART.
 * 		Enter an alphanumeric value between 1 and 10 characters in length.
 * 		This value will replace the previous password.
 * 		-> A return of 001.00 confirms that the password was successfully changed.
 * @param  value Specifies the value of the user password.
 * @retval None
 */
#define SET_USER_PASSWORD(value)                   	   \
		do {                                           \
			char command[30];                          \
			sprintf(command, "SET PASS=%s", value);\
			send_uart_command(command);                \
		} while (0)

/**
 * @brief  Displays the user lock state via UART.
 * 		-> A return of 000.00 indicates that the commands are unlocked.
 * 		-> A return of 001.00 indicates that the commands are locked.
 * @param  None
 * @retval None
 */
#define DISPLAY_USER_LOCK_STATE()    	 \
		do {                             \
			char command[30];            \
			sprintf(command, "LOCK");\
			send_uart_command(command);  \
		} while (0)


/***********************************************************************
 *							GLOBAL DEFINITIONS
 ***********************************************************************/

#define RXBUFFERSIZE_CRYOCOOLER 1000
#define TXBUFFERSIZE_CRYOCOOLER 3

#define MIN_TEMP_LIMIT 70
#define MAX_TEMP_LIMIT 290
#define MAX_POWER_LIMIT 250

typedef enum {
	INIT_STATE_RESET_CONTROLLER,
	INIT_STATE_SET_SOFT_STOP_MODE,
	INIT_STATE_SET_THERMOSTAT_MODE,
	INIT_STATE_SET_CONTROL_MODE,
	INIT_STATE_SET_TARGET_POWER_OUTPUT,
	INIT_STATE_SET_MINIMUM_POWER_OUTPUT,
	INIT_STATE_SET_MAXIMUM_POWER_OUTPUT,
	INIT_STATE_DISPLAY_OPERATING_STATE,
	INIT_STATE_DONE
} Initialization_SM_States;

typedef enum {
	OFF_STATE_DISPLAY_ERROR_CODE,
	OFF_STATE_DISPLAY_COLD_TIP_TEMPERATURE,
	OFF_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER,
	OFF_STATE_CHECK_PARAMETERS,
    OFF_STATE_DONE
} Off_SM_States;

typedef enum {
	ON_STATE_DISPLAY_ERROR_CODE,
	ON_STATE_DISPLAY_COLD_TIP_TEMPERATURE,
	ON_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER,
	ON_STATE_CHECK_PARAMETERS,
    ON_STATE_DONE
} On_SM_States;

typedef enum {
	ERROR_STATE_NO_ERROR,
	ERROR_STATE_OVERCURRENT_ERROR,
	ERROR_STATE_JUMPER_ERROR,
	ERROR_STATE_SERIALCOMM_ERROR,
	ERROR_STATE_NON_VOLMEM_ERROR,
	ERROR_STATE_WATCHDOG_ERROR,
	ERROR_STATE_TEMPERATURESENSOR_ERROR
} Error_SM_States;

typedef enum{
	CRYOCOOLER_ERROR_NONE,
	CRYOCOOLER_INTERNAL_ERROR,
	CRYOCOOLER_TEMP_ERROR,
	CRYOCOOLER_PWR_ERROR,
	CRYOCOOLER_ERROR_INVALID_RESPONSE,
	CRYOCOOLER_DISCONNECTION_ERROR
}CRYOCOOLER_ERR;

typedef enum{
    cryocooler_OFF,
	cryocooler_Start,
    cryocooler_ON,
	cryocooler_Stop,
	cryocooler_initialization,
	cryocooler_error,
}CRYOCOOLER_SM_states;

typedef enum{
	cryo_parameters_OK,
	cryo_parameters_FAULT,
	cryo_parameters_UNLOCKED=0,
	cryo_parameters_LOCKED
}CRYOCOOLER_flags;

typedef enum{
	RESET_F,
	TC,
	SET_PID,
	GET_PID,
	SAVE_PID,
	MODE,
	VERSION,
	SERIAL,
	GET_ERROR,
	P,
	E,
	SET_KI,
	GET_KI,
	STATE,
	SET_KP,
	GET_KP,
	SET_SSTOPM,
	GET_SSTOPM,
	SET_SSTOP,
	GET_SSTOP,
	SET_PWOUT,
	GET_PWOUT,
	SET_TTARGET,
	GET_TTARGET,
	SET_TBAND,
	GET_TBAND,
	SET_TSTATM,
	GET_TSTATM,
	TSTAT,
	SET_MIN,
	GET_MIN,
	SET_MAX,
	GET_MAX,
	SHOW_MX,
	SET_LOCK,
	SET_UNLOCK,
	SET_PASS,
	GET_LOCK,
	RESET_COMPLETE
}Cryocooler_commands;

/***********************************************************************
 *								STRUCTURES
 ***********************************************************************/

typedef struct ControllerParameters
{
	float		MODE	;		// Configured Cryocooler Type
	float		TSTATM	;		// Thermostat Mode
	float		TSTAT	;		// Thermostat State
	float		SSTOPM	;		// Soft-Stop Mode
	float		SSTOP	;		// Soft-Stop State
	float		PID		;		// Control Mode
	float		LOCK	;		// User Lock State
	char		PASS[10];		// User Password
	float		MAX		;		// User-Defined Maximum Power Output
	float		MIN		;		// User-Defined Minimum Power Output
	float		PWOUT	;		// Target Power Output
	float		TTARGET	;		// Target Temperature
	float		TBAND	;		// Temperature Band
	float		TEMP_KI	;		// Integral Constant of Temp. Control Loop
	float		TEMP_KP	;		// Proportional Constant of Temp. Control Loop

}st_ControllerParameters;

typedef union ErrorRegister{
	struct{
		uint8_t OverCurrent:1				; 	//< "Over Current error" bit
		uint8_t JumperError:1				; 	//< "Jumper Error" bit
		uint8_t SerialCommunicationError:1	;	//< "Serial Communication Error" bit
		uint8_t Non_VolatileMemoryError:1	;  	//< "Non-Volatile Memory Error" bit
		uint8_t WatchdogError:1				; 	//< "Watchdog Error" bit
		uint8_t TemperatureSensorError:1	;	//< "Temperature Sensor Error" bit
		uint8_t UnusedBits:2				;	//< "additional unused" bits
	}bits;
	uint8_t byte;								//< Representation in byte (8-bits) format
}st_CryocoolerErrorRegister;

typedef struct cryocoolerMeasures{
    float coldTipTemperature;
    float coolerPowerConsumed;
}st_MeasurableVariables;


typedef struct cryocoolerBuffer{
	char rxBuffer[RXBUFFERSIZE_CRYOCOOLER];	//buffer de recepcion
	char txBuffer[TXBUFFERSIZE_CRYOCOOLER];	//buffer de transmision
}st_cryocoolerBuffer;

typedef struct CryocoolerFunctions
{
	state		(*init_output)	(st_dig_output *);
	state		(*set_output)	(st_dig_output *, state);
	uint32_t 	(*init_uart)	(st_uart_module *);
	uint32_t 	(*receive_uart)	(st_uart_module *);
	uint32_t 	(*send_uart)	(st_uart_module *, uint32_t);
}st_Cryocooler_func;

typedef struct CryoTelCryocoolerGT
{
	st_dig_output				*soft_stop_pin;
	st_cryocoolerBuffer			uart_buffer;
	st_uart_module				*communicationPort;
	st_ControllerParameters 	operatingParameters;
	st_CryocoolerErrorRegister	errorRegister;
	st_MeasurableVariables      measurements;
	st_Cryocooler_func 			*functions;
	CRYOCOOLER_ERR				errorCode;
	CRYOCOOLER_flags			flag;
	CRYOCOOLER_SM_states		state;
	bool						rxComplete;
	uint64_t					*millisecElapsed;
}st_Cryocooler;
/***********************************************************************
 *					EXPORTED FUNCTIONS PROTOTYPES
 ***********************************************************************/

CRYOCOOLER_ERR cryocooler_Init(st_Cryocooler *);
void send_uart_command(char* command);
void execute_command_action(char *received_command);
void cryocoolerStateMachine(void);
#endif /* CRYOCOOLER_CRYOCOOLER_H_ */
