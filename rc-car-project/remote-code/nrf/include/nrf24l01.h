/*
 * nrf24l01.h
 *
 * Created: 27-09-2024 01:48:26
 *  Author: ksham
 */ 


#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "common.h"


// register address
#define CONFIG			0x00
#define EN_AA			0x01
#define EN_RXADDR		0x02
#define SETUP_AW		0x03
#define SETUP_RETR		0x04
#define RF_CH			0x05
#define RF_SETUP		0x06
#define STATUS			0x07
#define RX_PW_P1		0x12
#define RX_PW_P0		0x11
#define TX_ADDR			0x10
#define RX_ADDR_P0		0x0A
#define RX_ADDR_P1		0x0B

//////////////////////////////////////////////////////////////////////////
// nrf registers bit defs

// CONFIG bits, 0b00001000
#define MASK_RX_DR		6
#define MASK_TX_DS		5
#define MASK_MAX_RT		4
#define EN_CRC			3
#define CRCO			2
#define PWR_UP			1
#define PRIM_RX			0

// EN_AA bits, 0b00111111
#define ENAA_P5			5
#define ENAA_P4			4
#define ENAA_P3			3
#define ENAA_P2			2
#define ENAA_P1			1
#define ENAA_P0			0

// EN_RXADDR bits, 0b00000011
#define ERX_P5			5
#define ERX_P4			4
#define ERX_P3			3
#define ERX_P2			2
#define ERX_P1			1
#define ERX_P0			0


// SETUP_AW bits, 0b00000011
#define AW1				1
#define AW0				0

// SETUP_RETR bits, 0b00000011
#define ARD7			7
#define ARD6			6
#define ARD5			5
#define ARD4			4
#define ARC3			3
#define ARC2			2
#define ARC1			1
#define ARC0			0

// RF_CH bits, 0b00000010
//#define reserved		7
#define RF_CH6			6
#define RF_CH5			5
#define RF_CH4			4
#define RF_CH3			3
#define RF_CH2			2
#define RF_CH1			1
#define RF_CH0			0

// RF_SETUP bits, 0b00001111
#define PLL_LOCK		4
#define RF_DR			3
#define RF_PWR2			2
#define RF_PWR1			1
#define LNA_HCURR		0

// STATUS bits, 0b00001110
#define RX_DR			6
#define TX_DS			5
#define MAX_RT			4
#define RX_P_NO3		3	//r
#define RX_P_NO2		2	//r
#define RX_P_NO1		1	//r
#define TX_FULL			0	//r

// CD bits, 0b00000000
#define CD0				0

// RX_PW_P0 bits	
#define RX_PW_P05		5
#define RX_PW_P04		4
#define RX_PW_P03		3
#define RX_PW_P02		2
#define RX_PW_P01		1
#define RX_PW_P00		0


// FIFO_STATUS bits

#define FIFO_TX_REUSE	6
#define FIFO_TX_FULL	5
#define FIFO_TX_EMPTY	4
// #define RX_P_NO3	3
// #define RX_P_NO2	2
#define FIFO_RX_FULL	1
#define FIFO_RX_EMPTY	0


//////////////////////////////////////////////////////////////////////////
// nrf pin defs

#define NRF_CE_PIN		PORTB0		//0
#define NRF_CSN_PIN		SPI_SS_PIN	//1
#define NRF_IRQ_PIN		PORTD2		//2

// nrf port defs
#define NRF_CE_PORT		PORTB
#define NRF_CSN_PORT	SPI_PORT
#define NRF_IRQ_PORT	PORTD

// nrf data direction reg defs
#define NRF_CE_DDR		DDRB
#define NRF_CSN_DDR		SPI_DDR
#define NRF_IRQ_DDR		DDRD


//////////////////////////////////////////////////////////////////////////
/// nrf COMMANDS

#define _NOP			(0xFF)
#define R_RX_PAYLOAD	(0x61)
#define W_TX_PAYLOAD	(0xA0)

// d0 to d4 for reg address
#define R_REGISTER		(0x00)

// d0 to d4 for reg address
#define W_REGISTER		(0x20)

#define FLUSH_TX		(0xE1)
#define FLUSH_RX		(0xE2)



void nrf_w_reg(volatile uint8_t, volatile uint8_t);
volatile uint8_t nrf_r_reg(volatile uint8_t);
void nrf_tx_data(volatile uint8_t);
volatile uint8_t nrf_rx_data(void);

void nrf_tx_init(void);
void nrf_rx_init(void);
void nrf_irq_init(void);
void nrf_w_rx_addr(volatile uint8_t);
void nrf_w_tx_addr(volatile uint8_t);
void nrf_print_registers(void);

uint8_t get_status(void);
void flush_tx(void);

void nrf_transmit_string(uint8_t *);


#define NRF_CE_PIN_LOW		GPIO_PIN_LOW(NRF_CE_PORT,NRF_CE_PIN);
#define NRF_CE_PIN_HIGH		GPIO_PIN_HIGH(NRF_CE_PORT,NRF_CE_PIN);

#define NRF_CSN_PIN_HIGH	GPIO_PIN_HIGH(NRF_CSN_PORT,NRF_CSN_PIN);
#define NRF_CSN_PIN_LOW		GPIO_PIN_LOW(NRF_CSN_PORT,NRF_CSN_PIN);

#define NRF_CE_PULSE		{	NRF_CE_PIN_HIGH;\
								_delay_us(30);\
								NRF_CE_PIN_LOW;\
							}


#endif /* NRF24L01_H_ */