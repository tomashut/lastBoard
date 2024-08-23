/*
 * OD.h
 *
 *  Created on: 31 ene. 2024
 *      Author: CRINSURANCE 1
 */

#ifndef OD_H_
#define OD_H_

#ifdef __cplusplus               /* for compatibility with C++ environments  */
extern "C" {
#endif

/******************************************************************************
* INCLUDES
******************************************************************************/

#include "co_core.h"

/******************************************************************************
* PRIVATE VARIABLES
******************************************************************************/

#define MASTER_NODE_FREQUENCY   500000  // Frecuencia en Hz
#define SLAVE_NODE_FREQUENCY   	500000
#define TRANSFER_DATA_COMPLETE 	1
#define NO_TRANSFER_OCCURRED 	0

typedef struct {
	uint8_t  Obj1001_00_08;						//Error Register

	uint16_t Obj1017_00_10;					//Producer Heartbeat time

	/* allocate variables for ant values in FLASH */
	uint32_t Obj1000_00_20;			//Device type

	uint32_t Obj1014_00_20;			//COB-ID EMCY

	uint32_t Obj1018_01_20;			//Vendor-ID
	uint32_t Obj1018_02_20;			//Product code
	uint32_t Obj1018_03_20;			//Revision Number
	uint32_t Obj1018_04_20;			//Serial Number

	uint32_t Obj1200_01_20;			//SDO server parameter: COB-ID client to server
	uint32_t Obj1200_02_20;			//SDO server parameter: COB-ID server to client

	uint32_t Obj1280_01_20;			//COB-ID client to server (Transmit SDO)
	uint32_t Obj1280_02_20;			//COB-ID server to client (Receive SDO)
	uint8_t Obj1280_03_20;			//Node-ID of the SDO server

	uint32_t Obj1400_01_20;			//RPDO communication parameter: COB-ID used by TPDO
	uint32_t Obj1400_02_20;			//RPDO communication parameter: Trnsmission Type
	uint32_t Obj1400_05_20;			//RPDO communication parameter: Event Timer: 1.5 segs.

	uint32_t Obj1600_01_20;			//RPDO mapping parameter: Application object 1
	uint32_t Obj1600_02_20;			//RPDO mapping parameter: Application object 2
	uint32_t Obj1600_03_20;			//RPDO mapping parameter: Application object 3
	uint32_t Obj1600_04_20;			//RPDO mapping parameter: Application object 4
	uint32_t Obj1600_05_20;			//RPDO mapping parameter: Application object 5
	uint32_t Obj1600_06_20;			//RPDO mapping parameter: Application object 6
	uint32_t Obj1600_07_20;			//RPDO mapping parameter: Application object 7
	uint32_t Obj1600_08_20;			//RPDO mapping parameter: Application object 8

	uint8_t  Obj6000_01_20;			//SWITCH CRYOPRESSURE STATE MESSAGE OBJECT

	uint32_t Obj6000_02_20;			// PRESSURE SENSOR MEASUREMENT
	uint32_t Obj6000_03_20;			// PRESSURE SENSOR TEMPERATURE
	uint16_t Obj6000_04_20;			// COMPRESSOR SPEED
	uint16_t Obj6000_05_20;			// COMPRESSOR CURRENT
	uint8_t  Obj6000_06_20;			// CHILLER TEMPERATURE
	uint8_t  Obj6000_07_20;			// CHILLER TROUBLECODE
	uint32_t Obj6000_08_20;			// CRYOCOOLER POWER CONSUMED
	uint32_t Obj6000_09_20;			// CRYOCOOLER COLD-TIP TEMPERATURE
	uint32_t Obj6000_10_20;			// ADS1118 TEMP
	uint32_t Obj6000_11_20;			// CRYOPRESSURE STATE
	uint32_t Obj6000_12_20;			// CHILLER SET SPEED
	uint16_t Obj6000_13_20;			// Board Reset cause

	float 	 Obj6000_14_20;			// Cryocooler MODE
	float	 Obj6000_15_20;			// Cryocooler TSTAM
	float	 Obj6000_16_20;			// Cryocooler TSTAT
	float	 Obj6000_17_20;			// Cryocooler SSTOPM
	float	 Obj6000_18_20;			// Cryocooler SSTOP
	float	 Obj6000_19_20;			// Cryocooler PID
	CO_OBJ_STR Obj6000_20_20;		// Cryocooler PASS
	float	 Obj6000_21_20;			// Cryocooler LOCK
	float	 Obj6000_22_20;			// Cryocooler MAX
	float	 Obj6000_23_20;			// Cryocooler MIN
	float	 Obj6000_24_20;			// Cryocooler PWOUT
	float	 Obj6000_25_20;			// Cryocooler TTARGET
	float	 Obj6000_26_20;			// Cryocooler TBAND
	float	 Obj6000_27_20;			// Cryocooler TEMP_KI
	float	 Obj6000_28_20;			// Cryocooler TEMP_KP

	float	 Obj6000_29_20;			//SHUTDOWN TEMP
	float 	 Obj6000_30_20;			//DANGER TEMP
	uint8_t  Obj6000_31_20;			//Set chiller temp
	float 	 Obj6000_32_20;
	float 	 Obj6000_33_20;


}st_OD_Obj;


/******************************************************************************
* PUBLIC DEFINES
******************************************************************************/

/* Specify the EMCY-IDs for the application */
enum EMCY_CODES {
    APP_ERR_ID_SOMETHING = 0,
    APP_ERR_ID_HOT,

    APP_ERR_ID_NUM            /* number of EMCY error codes in application */
};

/******************************************************************************
* PUBLIC SYMBOLS
******************************************************************************/
extern struct CO_IF_T 			SlaveIf;
extern struct CO_NODE_SPEC_T 	SlaveSpec;
extern st_OD_Obj				DictSlave;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void 	CAN_enableInterrupt		(void);
void 	CAN_disableInterrupt	(void);
CO_ERR 	CANopen_slaveInit		(CO_NODE *);
void 	CANOpen_sendData		(CO_NODE *node);
void 	CSdoFinishCb			(CO_CSDO *csdo, uint16_t index, uint8_t sub, uint32_t code);
bool 	DATA_MAPPEABLE_TO_FLASH	(void);


#ifdef __cplusplus               /* for compatibility with C++ environments  */
}
#endif


#endif /* OD_H_ */
