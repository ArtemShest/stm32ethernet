/*
 * w5100s.c
 *
 *  Created on: Dec 22, 2022
 *      Author: artem
 */


#include "w5100s.h"
#include "main.h"

//-----------------------------------------------

extern SPI_HandleTypeDef hspi3;


//-----------------------------------------------

extern char str1[60];

//-----------------------------------------------

uint8_t macaddr[6]=MAC_ADDR;

extern uint8_t ipaddr[4];
extern uint8_t ipgate[4];
extern uint8_t ipmask[4];
extern uint16_t local_port;

uint8_t w5100_readReg(uint16_t addres)
{
	uint8_t buf[] = {W5100_READ, addres >> 8, addres};
	uint8_t *rbyte;
    SS_SELECT();
	HAL_SPI_Transmit(&hspi3, buf, 3, 1000);
	HAL_SPI_Receive(&hspi3, &rbyte, 1, 1000);
	SS_DESELECT();
	return rbyte;
}

void w5100_writeReg(uint16_t addres, uint8_t data) ////   [read/write]  [addrM]  [addrL]  [data]
{
  uint8_t buf[] = {W5100_WRITE, addres >> 8, addres, data};
  SS_SELECT();
//  __NOP();
  HAL_SPI_Transmit(&hspi3, buf, 4, 0xFFFFFFFF);
//  __NOP();
  SS_DESELECT();
}

void w5100_ini(void)
{
  //Hard Reset

// w5100
	printf ("start init");

  ETH_RST_GPIO_Port->BSRR = (uint32_t)ETH_RST_Pin << 16U;
  //HAL_Delay(1);
  ETH_RST_GPIO_Port->BSRR = ETH_RST_Pin;

  //HAL_GPIO_WritePin(ETH_RST_GPIO_Port, ETH_RST_Pin, GPIO_PIN_RESET);
  //HAL_Delay(1);
  //usDelay(500);
 // HAL_GPIO_WritePin(ETH_RST_GPIO_Port, ETH_RST_Pin, GPIO_PIN_SET);
 // HAL_Delay(8);


  //check VERR

  uint8_t aaa = 0;
  aaa = w5100_readReg(REG_VERR);
  printf (" %.2x00s VERR\r\n", aaa);


  // 1. Mode Register
 w5100_writeReg(REG_MR, 0x80);		// soft reset
  	  HAL_Delay(1);
	  aaa =  w5100_readReg(REG_MR);
  //__NOP();
	  printf ("1. Mode Register\r\n");
	  printf ("\t write %d to REG_MR 0x%.4x; read %d\r\n", 0x80, REG_MR,  aaa);
  	  HAL_Delay(1);
  // 2. Interrupt Mask Register

  w5100_writeReg(REG_IMR, S0_INT);  // Interrupt Mask Register = Socket_0 interrupt enable
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_IMR);
  	  printf ("2. Interrupt Mask Register\r\n");
  	  printf ("\t write %d to REG_IMR 0x%.4x; read %d\r\n", S0_INT, REG_IMR, aaa);
  	  HAL_Delay(1);
  //__NOP();
  // 3. Retry Time-value Register
  w5100_writeReg(REG_RTR0, 0x0f);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_RTR0);
  	  printf ("3. Retry Time-value Register\r\n");
      printf ("\t write %d to REG_RTR0 0x%.4x; read %d\r\n", 0x0f, REG_RTR0, aaa);
  	  HAL_Delay(1);
  w5100_writeReg(REG_RTR1, 0xA0);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_RTR1);
      printf ("\t write %d to REG_RTR1 0x%.4x; read %d\r\n", 0xA0, REG_RTR1, aaa);
  	  HAL_Delay(1);
  //__NOP();
  // 4. Retry Count Register
//  w5100_writeReg(REG_RCR, 0x08);
  w5100_writeReg(REG_RCR, 0x01);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_RCR);
  	  printf ("4. Retry Count Register\r\n");
      printf ("\t write %d to REG_RCR 0x%.4x; read %d\r\n", 0x01, REG_RCR, aaa);
  	  HAL_Delay(1);
  //__NOP();


  //HAL_Delay(100);
  	 w5100_writeReg(REG_GWR0,ipgate[0]); // gate ip
  	  	  HAL_Delay(1);
  	  	  aaa = w5100_readReg(REG_GWR0);
  	  	  printf ("5. Gate ip\r\n");
  	      printf ("\t write %d to REG_GWR0 0x%.4x; read %d\r\n", ipgate[0], REG_GWR0, aaa);
  	  	  HAL_Delay(1);
  	 // __NOP();
  	  w5100_writeReg(REG_GWR1,ipgate[1]);
  	  	  HAL_Delay(1);
  	  	  aaa = w5100_readReg(REG_GWR1);
  	      printf ("\t write %d to REG_GWR1 0x%.4x; read %d\r\n", ipgate[1], REG_GWR1, aaa);
  	  	  HAL_Delay(1);
  	  //__NOP();
  	  w5100_writeReg(REG_GWR2,ipgate[2]);
  	  	  HAL_Delay(1);
  	  	  aaa = w5100_readReg(REG_GWR2);
  	      printf ("\t write %d to REG_GWR2 0x%.4x; read %d\r\n", ipgate[2], REG_GWR2, aaa);
  	  	  HAL_Delay(1);
  	  //__NOP();
  	  w5100_writeReg(REG_GWR3,ipgate[3]);
  	  	  HAL_Delay(1);
  	  	  aaa = w5100_readReg(REG_GWR3);
  	      printf ("\t write %d to REG_GWR3 0x%.4x; read %d\r\n", ipgate[3], REG_GWR3, aaa);
  	  	  HAL_Delay(1);

  //Configute Net
  w5100_writeReg(REG_SHAR0,macaddr[0]); //mac
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR0);
	  	  printf ("6. MAC\r\n");
	      printf ("\t write %d to REG_SHAR0 0x%.4x; read %d\r\n", macaddr[0], REG_SHAR0, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SHAR1,macaddr[1]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR1);
      printf ("\t write %d to REG_SHAR1 0x%.4x; read %d\r\n", macaddr[1], REG_SHAR1, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SHAR2,macaddr[2]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR2);
      printf ("\t write %d to REG_SHAR2 0x%.4x; read %d\r\n", macaddr[2], REG_SHAR2, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SHAR3,macaddr[3]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR3);
      printf ("\t write %d to REG_SHAR3 0x%.4x; read %d\r\n", macaddr[3], REG_SHAR3, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SHAR4,macaddr[4]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR4);
      printf ("\t write %d to REG_SHAR4 0x%.4x; read %d\r\n", macaddr[4], REG_SHAR4, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SHAR5,macaddr[5]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SHAR5);
      printf ("\t write %d to REG_SHAR5 0x%.4x; read %d\r\n", macaddr[5], REG_SHAR5, aaa);
  	  HAL_Delay(1);
  //__NOP();

  //__NOP();
  w5100_writeReg(REG_SUBR0,ipmask[0]); //mask ip
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SUBR0);
  	  printf ("7. Mask ip\r\n");
      printf ("\t write %d to REG_SUBR0 0x%.4x; read %d\r\n", ipmask[0], REG_SUBR0, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SUBR1,ipmask[1]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SUBR1);
      printf ("\t write %d to REG_SUBR1 0x%.4x; read %d\r\n", ipmask[1], REG_SUBR1, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SUBR2,ipmask[2]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SUBR2);
      printf ("\t write %d to REG_SUBR2 0x%.4x; read %d\r\n", ipmask[2], REG_SUBR2, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SUBR3,ipmask[3]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SUBR3);
      printf ("\t write %d to REG_SUBR3 0x%.4x; read %d\r\n", ipmask[3], REG_SUBR3, aaa);
  	  HAL_Delay(1);

  w5100_writeReg(REG_SIPR0,ipaddr[0]); 	//ip
  	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_SIPR0);
  	  printf ("8. IP\r\n");
      printf ("\t write %d to REG_SIPR0 0x%.4x; read %d\r\n", ipaddr[0], REG_SIPR0, aaa);
	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SIPR1,ipaddr[1]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SIPR1);
      printf ("\t write %d to REG_SIPR1 0x%.4x; read %d\r\n", ipaddr[1], REG_SIPR1, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SIPR2,ipaddr[2]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SIPR2);
      printf ("\t write %d to REG_SIPR2 0x%.4x; read %d\r\n", ipaddr[2], REG_SIPR2, aaa);
  	  HAL_Delay(1);
  //__NOP();
  w5100_writeReg(REG_SIPR3,ipaddr[3]);
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_SIPR3);
      printf ("\t write %d to REG_SIPR3 0x%.4x; read %d\r\n", ipaddr[3], REG_SIPR3, aaa);
  	  HAL_Delay(1);

/*

  w5100_writeReg(REG_S0_PORT0, 0x00);		// Setting port
	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_S0_PORT0);
	  printf ("9. Setting port\r\n");
	  printf ("\t write %d to REG_S0_PORT0 0x%.4x; read %d\r\n", 0x00, REG_S0_PORT0, aaa);
	  HAL_Delay(1);
  w5100_writeReg(REG_S0_PORT1, 10);		// Setting port
  	  HAL_Delay(1);
  	  aaa = w5100_readReg(REG_S0_PORT1);
  	  printf ("\t write %d to REG_S0_PORT1 0x%.4x; read %d\r\n", 10, REG_S0_PORT1, aaa);
  	  HAL_Delay(1);
*/
  //Настраиваем сокет 0



  //w5100_writeReg(REG_RMSR, 0x55);		// RX memory of Socket_0 = 8kB, others = 0kB
  w5100_writeReg(REG_RMSR, 0x0); // 1kb 1kb 1kb 1kb
	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_RMSR);
	  printf ("10. RX memory 1kb 1kb 1kb 1kb\r\n");
	  printf ("\t write %d to REG_RMSR 0x%.4x; read %d\r\n", 0x0, REG_RMSR, aaa);
	  HAL_Delay(1);
  //w5100_writeReg(REG_TMSR, 0x55);		// TX memory of Socket_0 = 8kB, others = 0kB
  w5100_writeReg(REG_TMSR, 0x0); // 1kb 1kb 1kb 1kb
	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_TMSR);
	  printf ("11. TX memory 1kb 1kb 1kb 1kb\r\n");
	  printf ("\t write %d to REG_TMSR 0x%.4x; read %d\r\n", 0x0, REG_TMSR, aaa);
	  HAL_Delay(1);


  //w5500_writeReg(REG_S0_IMR, *(uint8_t*)(RECV));			// RX interrupt enable
/*
  w5100_writeReg(REG_S0_MR, TCP_MODE);		// Setting TCP protocol
	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_S0_MR);
	  printf ("12. Setting TCP protocol\r\n");
	  printf ("\t write %d to REG_S0_MR 0x%.4x; read %d\r\n", TCP_MODE, REG_S0_MR, aaa);
	  HAL_Delay(1);
  w5100_writeReg(REG_S0_CR, SOCKET_OPEN);	// Socket OPEN
	  HAL_Delay(1);
	  aaa = w5100_readReg(REG_S0_CR);
	  printf ("13. Socket OPEN\r\n");
	  printf ("\t write %d to REG_S0_CR 0x%.4x; read %d\r\n", SOCKET_OPEN, REG_S0_CR, aaa);
	  HAL_Delay(1);

*/

}

//-----------------------------------------------

static void Error (void)
{
	//HAL_UART_Transmit(&huart3,(uint8_t*)"Error!rn",8,0x1000);
}

//-----------------------------------------------
