/*
 * can_config.h
 *
 *  Created on: Apr 4, 2024
 *      Author: CRINSURANCE 1
 */

#ifndef LIBRARY_BASICCAN_CAN_CONFIG_H_
#define LIBRARY_BASICCAN_CAN_CONFIG_H_

#include "basicCAN.h"

enum{
	enum_can_inSystem_1,
	enum_can_inSystem_2,
	enum_can_inSystem_3,
	eunm_can_inSystem
};

typedef struct can_bus_t{
	st_basicCan *CAN;
}st_can_bus;

CAN_ERR		can_Init				(st_can_bus *);
CAN_ERR		can_receive				(st_can_bus *);
CAN_ERR 	can_send				(st_can_bus *);
CAN_ERR 	can_enable				(st_can_bus *this, uint32_t baudrate);
CAN_ERR 	can_reset				(st_can_bus *this);
CAN_ERR 	can_close				(st_can_bus *this);
st_can_bus	*can_config_InitPhyCAN	(uint32_t);

typedef CAN_ERR	(*CO_IF_CAN_INIT_FUNC  )(st_can_bus*);
typedef CAN_ERR (*CO_IF_CAN_READ_FUNC  )(st_can_bus*);
typedef CAN_ERR (*CO_IF_CAN_SEND_FUNC  )(st_can_bus*);
typedef CAN_ERR	(*CO_IF_CAN_ENABLE_FUNC)(st_can_bus*, uint32_t);
typedef CAN_ERR (*CO_IF_CAN_RESET_FUNC )(st_can_bus*);
typedef CAN_ERR (*CO_IF_CAN_CLOSE_FUNC )(st_can_bus*);

typedef struct CO_IF_CAN_DRV_T {
    CO_IF_CAN_INIT_FUNC   Init;
    CO_IF_CAN_ENABLE_FUNC Enable;
    CO_IF_CAN_READ_FUNC   Read;
    CO_IF_CAN_SEND_FUNC   Send;
    CO_IF_CAN_RESET_FUNC  Reset;
    CO_IF_CAN_CLOSE_FUNC  Close;
} CO_IF_CAN_DRV;


#endif /* LIBRARY_BASICCAN_CAN_CONFIG_H_ */
