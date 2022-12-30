/*
 * net.c
 *
 *  Created on: Dec 22, 2022
 *      Author: artem
 */


#include "net.h"

//-----------------------------------------------


//-----------------------------------------------

uint8_t ipaddr[4]=IP_ADDR;

uint8_t ipgate[4]=IP_GATE;

uint8_t ipmask[4]=IP_MASK;

uint16_t local_port = LOCAL_PORT;

char str1[60]={0};

//-----------------------------------------------

void packet_receive(void)
{

}
//-----------------------------------------------

void net_poll(void)
{
  packet_receive();
}

void net_ini(void)
{
	w5100_ini();
}

//-
