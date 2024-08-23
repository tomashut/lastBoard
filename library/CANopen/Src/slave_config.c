/******************************************************************************
   Copyright 2020 Embedded Office GmbH & Co. KG

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ******************************************************************************/

/******************************************************************************
 * INCLUDES
 ******************************************************************************/


/* select application drivers: */
#include <slave_config.h>
#include "drv_timer_swcycle.h"                /* Timer driver                */
#include "drv_nvm_sim.h" 	                  /* NVM driver                  */

/******************************************************************************
 * PRIVATE DEFINES
 ******************************************************************************/

/* Define some default values for our CANopen node: */
#define SLAVE_NODE_ID       16u                  /* CANopen node ID             */
#define SLAVE_BAUDRATE      500000u             /* CAN baudrate                */
#define SLAVE_TMR_N         16u                 /* Number of software timers   */
#define SLAVE_TICKS_PER_SEC 1000u               /* Timer clock frequency in Hz */
#define SLAVE_OBJ_N         255u                /* Object dictionary max size  */

/******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/

/* allocate variables for dynamic runtime value in RAM */
uint8_t password[10]={'S','T','I','R','L','I','N','G'};
st_OD_Obj DictSlave={
		.Obj1001_00_08 = 0,
		.Obj1017_00_10=1000,

		.Obj6000_01_20 = 0,
		.Obj6000_02_20 = 0,
		.Obj6000_03_20 = 0,
		.Obj6000_04_20 = 0,
		.Obj6000_05_20 = 0,
		.Obj6000_06_20 = 0,
		.Obj6000_07_20 = 0,
		.Obj6000_08_20 = 0,
		.Obj6000_09_20 = 0,
		.Obj6000_10_20 = 0,
		.Obj6000_11_20 = 0,
		.Obj6000_12_20 = 0,
		.Obj6000_13_20 = 1700, //Chiller's speed
		//Cryocooler operating parameters
		.Obj6000_14_20 = 2,
		.Obj6000_15_20 = 0,
		.Obj6000_16_20 = 0,
		.Obj6000_17_20 = 0,
		.Obj6000_18_20 = 0,
		.Obj6000_19_20 = 2,
		.Obj6000_20_20={0,password},
		.Obj6000_21_20 = 0,
		.Obj6000_22_20 = 300,
		.Obj6000_23_20 = 50,
		.Obj6000_24_20 = 0,
		.Obj6000_25_20 = 77,
		.Obj6000_26_20 = 0.5,
		.Obj6000_27_20 = 1,
		.Obj6000_28_20 = 50,
		.Obj6000_29_20 = 0,
		.Obj6000_30_20 = 50,
		.Obj6000_31_20 = 25,
		.Obj6000_32_20 = 0,
		.Obj6000_33_20 = 0,

		.Obj1000_00_20=0x00000000L,
		.Obj1014_00_20=0x00000080L,
		.Obj1018_01_20=0x00000000L,
		.Obj1018_02_20=0x00000000L,
		.Obj1018_03_20=0x00000000L,
		.Obj1018_04_20=0x00000000L,

		.Obj1200_01_20 = CO_COBID_SDO_RESPONSE(),
		.Obj1200_02_20 = CO_COBID_SDO_REQUEST(),

		.Obj1280_01_20 = CO_COBID_SDO_RESPONSE()-SLAVE_NODE_ID,
		.Obj1280_02_20 = CO_COBID_SDO_REQUEST(),
		.Obj1280_03_20 = 1u,

		.Obj1400_01_20 = CO_COBID_RPDO_DEFAULT(0),
		.Obj1400_02_20 = 255,
		.Obj1400_05_20 = 0x05DC,
		.Obj1600_01_20 = CO_LINK(0x2100, 0x05,32),
		.Obj1600_02_20 = CO_LINK(0x2100, 0x06, 8),
		.Obj1600_03_20 = CO_LINK(0x2100, 0x07,16),
		.Obj1600_04_20 = CO_LINK(0x2100, 0x08, 8),

};
/* define the static object dictionary */
static struct CO_OBJ_T dictSlaveOD[SLAVE_OBJ_N] = {
		{CO_KEY(0x1000, 0, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1000_00_20)},
		{CO_KEY(0x1001, 0, CO_OBJ_____R_), CO_TUNSIGNED8 , 	(CO_DATA)(&DictSlave.Obj1001_00_08)},
		{CO_KEY(0x1014, 0, CO_OBJ_____R_), CO_TEMCY_ID,    	(CO_DATA)(&DictSlave.Obj1014_00_20)},
		{CO_KEY(0x1017, 0, CO_OBJ_____RW), CO_THB_PROD,    	(CO_DATA)(&DictSlave.Obj1017_00_10)},

		{CO_KEY(0x1018, 0, CO_OBJ_D___R_), CO_TUNSIGNED8 , 	(CO_DATA)(4)			              },
		{CO_KEY(0x1018, 1, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1018_01_20)},
		{CO_KEY(0x1018, 2, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1018_02_20)},
		{CO_KEY(0x1018, 3, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1018_03_20)},
		{CO_KEY(0x1018, 4, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1018_04_20)},

		{CO_KEY(0x1200, 0, CO_OBJ_D___R_), CO_TUNSIGNED8 , 	(CO_DATA)(2)			              },
		{CO_KEY(0x1200, 1, CO_OBJ__N__R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1200_01_20)},
		{CO_KEY(0x1200, 2, CO_OBJ__N__R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1200_02_20)},

		{CO_KEY(0x1280, 0, CO_OBJ_D___R_), CO_TUNSIGNED8, 	(CO_DATA)(3)						  },
		{CO_KEY(0x1280, 1, CO_OBJ__N__R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1280_01_20)},
		{CO_KEY(0x1280, 2, CO_OBJ__N__R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1280_02_20)},
		{CO_KEY(0x1280, 3, CO_OBJ_____R_), CO_TUNSIGNED8, 	(CO_DATA)(&DictSlave.Obj1280_03_20)},

		{CO_KEY(0x1400, 0, CO_OBJ_D___R_), CO_TUNSIGNED8 , 	(CO_DATA)(3)                        },
		{CO_KEY(0x1400, 1, CO_OBJ__N__R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1400_01_20)},
		{CO_KEY(0x1400, 2, CO_OBJ_D___R_), CO_TUNSIGNED8 , 	(CO_DATA)(&DictSlave.Obj1400_02_20)},
		{CO_KEY(0x1400, 5, CO_OBJ_D___R_), CO_TUNSIGNED16 ,	(CO_DATA)(&DictSlave.Obj1400_05_20)},

		{CO_KEY(0x1600, 0, CO_OBJ_D___R_), CO_TUNSIGNED8 , 	(CO_DATA)(8)                        },
		{CO_KEY(0x1600, 1, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_01_20)},
		{CO_KEY(0x1600, 2, CO_OBJ_____R_), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj1600_02_20)},
		{CO_KEY(0x1600, 3, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_03_20)},
		{CO_KEY(0x1600, 4, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_04_20)},
		{CO_KEY(0x1600, 5, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_05_20)},
		{CO_KEY(0x1600, 6, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_06_20)},
		{CO_KEY(0x1600, 7, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_07_20)},
		{CO_KEY(0x1600, 8, CO_OBJ_____R_), CO_TUNSIGNED32, 	(CO_DATA)(&DictSlave.Obj1600_08_20)},

		{CO_KEY(0x6000, 0, CO_OBJ_D___R_), CO_TUNSIGNED8, 	(CO_DATA)(33)             		  },
		{CO_KEY(0x6000, 1, CO_OBJ___APRW), CO_TUNSIGNED8,	(CO_DATA)(&DictSlave.Obj6000_01_20)},	// START SYSTEM BYTE
		{CO_KEY(0x6000, 2, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_02_20)},	// PRESSURE SENSOR MEASUREMENT
		{CO_KEY(0x6000, 3, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_03_20)},	// PRESSURE SENSOR TEMP MEASUREMENT
		{CO_KEY(0x6000, 4, CO_OBJ___APRW), CO_TUNSIGNED16,	(CO_DATA)(&DictSlave.Obj6000_04_20)},	// COMPRESSOR SPEED
		{CO_KEY(0x6000, 5, CO_OBJ___APRW), CO_TUNSIGNED16,	(CO_DATA)(&DictSlave.Obj6000_05_20)},	// COMPRESSOR CURRENT
		{CO_KEY(0x6000, 6, CO_OBJ___APRW), CO_TUNSIGNED8,	(CO_DATA)(&DictSlave.Obj6000_06_20)},	// CHILLER
		{CO_KEY(0x6000, 7, CO_OBJ___APRW), CO_TUNSIGNED8,	(CO_DATA)(&DictSlave.Obj6000_07_20)},	// CHILLER
		{CO_KEY(0x6000, 8, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_08_20)},	// CRYOCOOLER COLD-TIP TEMP
		{CO_KEY(0x6000, 9, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_09_20)},	// CRYOCOOLER CONSUMED POWER
		{CO_KEY(0x6000,10, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_10_20)},	// ADS1118 TEMPERATURE
		{CO_KEY(0x6000,11, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_11_20)},	// CRYOPRESSURE STATES
		{CO_KEY(0x6000,12, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_12_20)},	// CHILLER SET SDPEED
		{CO_KEY(0x6000,13, CO_OBJ___APRW), CO_TUNSIGNED16,	(CO_DATA)(&DictSlave.Obj6000_13_20)},	// Board reset cause

		{CO_KEY(0x6000,14, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_14_20)},	// Cryocooler MODE
		{CO_KEY(0x6000,15, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_15_20)},	// Cryocooler TSTAM
		{CO_KEY(0x6000,16, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_16_20)},	// Cryocooler TSTAT
		{CO_KEY(0x6000,17, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_17_20)},	// Cryocooler SSTOPM
		{CO_KEY(0x6000,18, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_18_20)},	// Cryocooler SSTOP
		{CO_KEY(0x6000,19, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_19_20)},	// Cryocooler PID
		{CO_KEY(0x6000,20, CO_OBJ_____RW), CO_TSTRING,		(CO_DATA)(&DictSlave.Obj6000_20_20)},	// Cryocooler PASS
		{CO_KEY(0x6000,21, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_21_20)},	// Cryocooler LOCK
		{CO_KEY(0x6000,22, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_22_20)},	// Cryocooler MAX
		{CO_KEY(0x6000,23, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_23_20)},	// Cryocooler MIN
		{CO_KEY(0x6000,24, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_24_20)},	// Cryocooler PWOUT
		{CO_KEY(0x6000,25, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_25_20)},	// Cryocooler TTARGET
		{CO_KEY(0x6000,26, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_26_20)},	// Cryocooler TBAND
		{CO_KEY(0x6000,27, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_27_20)},	// Cryocooler TEMP_KI
		{CO_KEY(0x6000,28, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_28_20)},	// Cryocooler TEMP_KP

		{CO_KEY(0x6000,29, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_29_20)},	//
		{CO_KEY(0x6000,30, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_30_20)},
		{CO_KEY(0x6000,31, CO_OBJ___APRW), CO_TUNSIGNED8,	(CO_DATA)(&DictSlave.Obj6000_31_20)},
		{CO_KEY(0x6000,32, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_32_20)},
		{CO_KEY(0x6000,33, CO_OBJ___APRW), CO_TUNSIGNED32,	(CO_DATA)(&DictSlave.Obj6000_33_20)},

		CO_OBJ_DICT_ENDMARK  /* mark end of used objects */
};

/* Each software timer needs some memory for managing
 * the lists and states of the timed action events.
 */
static CO_TMR_MEM TmrMem[SLAVE_TMR_N];

/* Each SDO server needs memory for the segmented or
 * block transfer requests.
 */
static uint8_t SdoSrvMem[CO_SSDO_N * CO_SDO_BUF_BYTE];


/* Specify the EMCY error codes with the corresponding
 * error register bit. There is a collection of defines
 * for the predefined emergency codes CO_EMCY_CODE...
 * and for the error register bits CO_EMCY_REG... for
 * readability. You can use plain numbers, too.
 */
static CO_EMCY_TBL AppEmcyTbl[APP_ERR_ID_NUM] = {
		{ CO_EMCY_REG_GENERAL, CO_EMCY_CODE_GEN_ERR          }, /* APP_ERR_CODE_SOMETHING */
		{ CO_EMCY_REG_TEMP   , CO_EMCY_CODE_TEMP_AMBIENT_ERR }  /* APP_ERR_CODE_HAPPENS   */
};

/* Select the drivers for your application. For possible
 * selections, see the directory /drivers. In this example
 * we select the driver templates. You may fill them with
 * your specific hardware functionality.
 */
static struct CO_IF_DRV_T AppDriver = {
		&SimCanDrivers,
		&SwCycleTimerDriver,
		&SimNvmDriver
};


/******************************************************************************
 * PUBLIC VARIABLES
 ******************************************************************************/

/* Collect all node specification settings in a single
 * structure for initializing the node easily.
 */
struct CO_NODE_SPEC_T SlaveSpec = {
		SLAVE_NODE_ID,             /* default Node-Id                */
		SLAVE_BAUDRATE,            /* default Baudrate               */
		&dictSlaveOD[0],             /* pointer to object dictionary   */
		SLAVE_OBJ_N,               /* object dictionary max length   */
		&AppEmcyTbl[0],          /* EMCY code & register bit table */
		&TmrMem[0],              /* pointer to timer memory blocks */
		SLAVE_TMR_N,               /* number of timer memory blocks  */
		SLAVE_TICKS_PER_SEC,       /* timer clock frequency in Hz    */
		&AppDriver,              /* select drivers for application */
		&SdoSrvMem[0]            /* SDO Transfer Buffer Memory     */
};

/* Collect the link to hardware driver functions and
 * parent node in a single structure to initializing the Interface easily.
 */
struct CO_IF_T SlaveIf={
		NULL,
		&AppDriver
};

CO_NODE *nodo;

/***********************************************************************
 *							FUNCTIONS
 **********************************************************************/
bool DATA_MAPPEABLE_TO_FLASH(void){
	if(DICT_CHILLER_SET_SPEED <= CO_DEV(nodo->Sdo[0].Idx, nodo->Sdo[0].Sub) && CO_DEV(nodo->Sdo[0].Idx, nodo->Sdo[0].Sub) <= DICT_CRYOCOOLER_TEMP_KP){
		return true;
	}
	return false;
}

void CAN_disableInterrupt(void)
{
	HAL_CAN_DeactivateNotification(&nodo->CAN_bus.CAN->can_phy.handlerCan,nodo->CAN_bus.CAN->can_phy.activeITs);
}

void CAN_enableInterrupt(void)
{
	HAL_CAN_ActivateNotification(&nodo->CAN_bus.CAN->can_phy.handlerCan,nodo->CAN_bus.CAN->can_phy.activeITs);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_disableInterrupt();
	CONodeProcess(nodo);
	nodo->transferState = TRANSFER_DATA_COMPLETE;
}

CO_ERR CANopen_slaveInit(CO_NODE *node){
	CO_ERR err=CO_ERR_NONE;
	SlaveIf.Node=node;
	node->If = SlaveIf;
	SlaveSpec.TmrFreq = SLAVE_NODE_FREQUENCY;
	CONodeInit(node, &SlaveSpec);
	CONmtSetMode(&node->Nmt, CO_OPERATIONAL);
	err=CONodeGetErr(node);
	if (err!=CO_ERR_NONE)
	{
		return err;
	}
	CONodeStart(node);
	//Deberiamos poner un COIfCan para enviar una resincronizacion en caso de que sea necesario
	nodo = node;
	return err;
}


/******************************************************************************
 * USER CALLBACKS
 ******************************************************************************/

void CSdoFinishCb(CO_CSDO *csdo, uint16_t index, uint8_t sub, uint32_t code)
{
	if (code == 0)
	{

		/* data written successfully in remote node */

	}
	else
	{
		/* a timeout or abort is detected during SDO transfer  */

	}
}
