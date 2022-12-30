/*
 * net.h
 *
 *  Created on: Dec 22, 2022
 *      Author: artem
 */

#ifndef INC_NET_H_
#define INC_NET_H_



#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "w5100s.h"

//--------------------------------------------------

#define IP_ADDR {192,168,1,15}

#define IP_GATE {192,168,1,1}

#define IP_MASK {255,255,255,0}

#define LOCAL_PORT 80

//--------------------------------------------------

#define be16toword(a) ((((a)>>8)&0xff)|(((a)<<8)&0xff00))

void packet_receive(void);
void net_poll(void);
void net_ini(void);


#endif /* INC_NET_H_ */
