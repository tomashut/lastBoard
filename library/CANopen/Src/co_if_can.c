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

#include "co_core.h"

/******************************************************************************
* PUBLIC FUNCTIONS
******************************************************************************/
	st_can_bus* busCAN;
	enum{
		can1=enum_can_inSystem_1,
		can2=enum_can_inSystem_2
	};

	const CO_IF_CAN_DRV SimCanDrivers={
			.Init	= &can_Init,
			.Read	= &can_receive,
			.Send	= &can_send,
			.Enable	= &can_enable,
			.Reset	= &can_reset,
			.Close	= &can_close
	};

/*
* see function definition
*/
void COIfCanInit(CO_IF *cif, struct CO_NODE_T *node)
{
    const CO_IF_CAN_DRV *can = cif->Drv->Can;
//    (void)node;
    node->CAN_masterInstance=*can_config_InitPhyCAN(can1);
    can->Init(&node->CAN_masterInstance);
    node->CAN_bus=*can_config_InitPhyCAN(can2);
    can->Init(&node->CAN_bus);
    busCAN=&node->CAN_bus;
}

/*
* see function definition
*/
int16_t COIfCanRead (CO_IF *cif, CO_IF_FRM *frm)
{
	int16_t err;
	const CO_IF_CAN_DRV *can = cif->Drv->Can;

	err = can->Read(busCAN);

	switch (busCAN->CAN->can_phy.rxHeader.IDE)
	{
	case CAN_ID_STD:frm->Identifier=busCAN->CAN->can_phy.rxHeader.StdId; break;
	case CAN_ID_EXT:frm->Identifier=busCAN->CAN->can_phy.rxHeader.ExtId; break;
	}
	frm->DLC=busCAN->CAN->can_phy.rxHeader.DLC;
	frm->Data[0]=busCAN->CAN->can_phy.rxData[0];
	frm->Data[1]=busCAN->CAN->can_phy.rxData[1];
	frm->Data[2]=busCAN->CAN->can_phy.rxData[2];
	frm->Data[3]=busCAN->CAN->can_phy.rxData[3];
	frm->Data[4]=busCAN->CAN->can_phy.rxData[4];
	frm->Data[5]=busCAN->CAN->can_phy.rxData[5];
	frm->Data[6]=busCAN->CAN->can_phy.rxData[6];
	frm->Data[7]=busCAN->CAN->can_phy.rxData[7];

	if (err != (int16_t)0) {
		cif->Node->Error = CO_ERR_IF_CAN_READ;
		return -1;
	}
	return (sizeof(CO_IF_FRM));
}

/*
* see function definition
*/
int16_t COIfCanSend(CO_IF *cif, CO_IF_FRM *frm)
{
	int16_t err;
	const CO_IF_CAN_DRV *can = cif->Drv->Can;

	//	/* Configurar la estructura de transferencia de mensaje */
	if ((frm->Identifier & 0xFFFFF800) != 0)
	{/*El ID es de 29bits (Extendido) */
		busCAN->CAN->can_phy.txHeader.IDE = CAN_ID_EXT;
		busCAN->CAN->can_phy.txHeader.ExtId= frm->Identifier;
	}
	else
	{/*Si el ID es de 11bits (Estandar) */
		busCAN->CAN->can_phy.txHeader.IDE = CAN_ID_STD;
		busCAN->CAN->can_phy.txHeader.StdId= frm->Identifier;
	}
	if (1>0)
	{/*-------------- DATA FRAME ----------------*/
		busCAN->CAN->can_phy.txHeader.RTR = CAN_RTR_DATA;
	}
	else
	{/*------------- REMOTE FRAME ---------------*/
		busCAN->CAN->can_phy.txHeader.RTR = CAN_RTR_REMOTE;
	}
	busCAN->CAN->can_phy.txHeader.DLC= frm->DLC;

	for (int i = 0; i < frm->DLC; ++i) {
		busCAN->CAN->can_phy.txData[i]=frm->Data[i];
	}

	err = can->Send(busCAN);

	if (err != (int16_t)0) {
		cif->Node->Error = CO_ERR_IF_CAN_SEND;
		return -1;
	}
	return (sizeof(CO_IF_FRM));
}

/*
* see function definition
*/
void COIfCanReset(CO_IF *cif)
{
    const CO_IF_CAN_DRV *can = cif->Drv->Can;
    can->Reset(busCAN);
}

/*
* see function definition
*/
void COIfCanClose(CO_IF *cif)
{
    const CO_IF_CAN_DRV *can = cif->Drv->Can;
    can->Close(busCAN);
}

/*
* see function definition
*/
void COIfCanEnable(CO_IF *cif, uint32_t baudrate)
{
    const CO_IF_CAN_DRV *can = cif->Drv->Can;

    if (baudrate == (uint32_t)0) {
    	baudrate = cif->Node->Baudrate;
    } else {
      	cif->Node->Baudrate = baudrate;
    }

    can->Enable(busCAN,baudrate);
}
