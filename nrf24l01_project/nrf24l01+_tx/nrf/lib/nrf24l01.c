/*
 * nrf24l01.c
 *
 * Created: 27-09-2024 01:48:05
 *  Author: ksham
 */ 

#include "nrf24l01.h"



void nrf_send_cmd(volatile uint8_t cmd)
{
	volatile uint8_t status = 0;
	
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	status = spi_rw_byte(cmd);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
}

void nrf_w_reg(volatile uint8_t w_reg_addr, volatile uint8_t reg_value)
{
	volatile uint8_t status = 0;
	
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	w_reg_addr = W_REGISTER | (w_reg_addr & 0x1F);	// prepare write reg cmd
	
	status = spi_rw_byte(w_reg_addr);
	_delay_us(10);
	spi_rw_byte(reg_value);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
}

volatile uint8_t nrf_r_reg(volatile uint8_t r_reg_addr)
{
	volatile uint8_t data = 0, status = 0;
	
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	r_reg_addr = R_REGISTER | (r_reg_addr & 0x1F);	// prepare read reg cmd
	
	status = spi_rw_byte(r_reg_addr);
	_delay_us(10);
	data = spi_rw_byte(_NOP);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
	
	return data;
}


void nrf_w_rx_addr(volatile uint8_t addr)
{
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	addr = W_REGISTER | (addr & 0x1F);	// prepare write reg cmd
	
	spi_rw_byte(addr);
	_delay_us(10);
	//0x65646f4e32
	// lsb written first
	spi_rw_byte(0x31);
	_delay_us(10);
	spi_rw_byte(0x4e);
	_delay_us(10);
	spi_rw_byte(0x6f);
	_delay_us(10);
	spi_rw_byte(0x64);
	_delay_us(10);
	spi_rw_byte(0x65);
	_delay_us(10);
	
	
	
	NRF_CSN_PIN_HIGH;
}

void nrf_w_tx_addr(volatile uint8_t addr)
{
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	addr = W_REGISTER | (addr & 0x1F);	// prepare write reg cmd
	
	spi_rw_byte(addr);
	_delay_us(10);
	//0x65646f4e32
	// lsb written first
	spi_rw_byte(0x32);
	_delay_us(10);
	spi_rw_byte(0x4e);
	_delay_us(10);
	spi_rw_byte(0x6f);
	_delay_us(10);
	spi_rw_byte(0x64);
	_delay_us(10);
	spi_rw_byte(0x65);
	_delay_us(10);
	
	
	
	NRF_CSN_PIN_HIGH;
}

void nrf_r_addr(volatile uint8_t reg, volatile uint8_t* addr)
{
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	reg = R_REGISTER | (reg & 0x1F);	// prepare write reg cmd
	
	spi_rw_byte(reg);
	_delay_us(10);
	addr[0] = spi_rw_byte(_NOP);
	_delay_us(10);
	addr[1] = spi_rw_byte(_NOP);
	_delay_us(10);
	addr[2] = spi_rw_byte(_NOP);
	_delay_us(10);
	addr[3] = spi_rw_byte(_NOP);
	_delay_us(10);
	addr[4] = spi_rw_byte(_NOP);
	_delay_us(10);
	
	NRF_CSN_PIN_HIGH;
}

void nrf_irq_init(void)
{
	PORTD |= (1<<2);
	DDRD &= ~(1<<2);
	
	EICRA |= (1<<1);	// falling edge trigger
	EIMSK |= (1<<0);	// enable interrupt 0
	
	/*GPIO_DDR_MODE(NRF_IRQ_DDR,NRF_IRQ_PIN,INPUT);
	GPIO_PULLUP_ON(NRF_IRQ_PORT,NRF_IRQ_PIN);
	
	SET_INT_TRIG_LEVEL(FALLING_EDGE);
	
	ENABLE_INTERRUPT(EXT_INTERRUPT_REG,EXTERNAL_INTERRUPT_0);*/
}

void nrf_tx_init(void)
{	
	GPIO_DDR_MODE(NRF_CE_DDR,NRF_CE_PIN,OUTPUT);
	
	// initialise interrupt
	//nrf_irq_init();
	
	// ce low, no rx/tx
	NRF_CE_PIN_LOW;	// spi still works
	
	//csn high, no spi
	NRF_CSN_PIN_HIGH;
	
	_delay_ms(100);// power up module
	
	
	nrf_w_reg(EN_AA,0x03);
	
	nrf_w_reg(SETUP_RETR,0x15);
	
	nrf_w_reg(EN_RXADDR,0x03);
	
	nrf_w_rx_addr(RX_ADDR_P0);
	
	nrf_w_tx_addr(RX_ADDR_P1);
	nrf_w_tx_addr(TX_ADDR);
	
	nrf_w_reg(RX_PW_P1,0x01);
	nrf_w_reg(RX_PW_P0,0x01);
	
	// transmit mode
	nrf_w_reg(CONFIG,0x7E);
	
	nrf_w_reg(STATUS,0x70);
	
	nrf_send_cmd(FLUSH_TX);
	nrf_send_cmd(FLUSH_RX);
	
	//NRF_CE_PIN_HIGH;	//start receiving
	_delay_ms(100);
	
}

void nrf_print_addr(volatile uint8_t* addr)
{
	volatile uint8_t i = 0;
	
	for(i = 0;i<5;i++)
	{
		uart_send_integer(addr[i]);
	}
}

void nrf_print_registers(void)
{
	volatile uint8_t reg = 0;
	volatile uint8_t addr[6] = {0};
	
	uart_print("***  NRF Internal Register Configurations  ***");
	
	reg = nrf_r_reg(EN_AA);
	uart_send_string("en_aa = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(SETUP_RETR);
	uart_send_string("setup_retr = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(EN_RXADDR);
	uart_send_string("en_rxaddr = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(SETUP_AW);
	uart_send_string("setup_aw = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RF_CH);
	uart_send_string("rf_ch = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RF_SETUP);
	uart_send_string("rf_setup = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RX_PW_P0);
	uart_send_string("rx_pw_p0 = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RX_PW_P1);
	uart_send_string("rx_pw_p1 = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(CONFIG);
	uart_send_string("config = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	nrf_r_addr(TX_ADDR,addr);
	uart_send_string("tx_addr = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	nrf_r_addr(RX_ADDR_P0,addr);
	uart_send_string("rx_addr_p0 = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	nrf_r_addr(RX_ADDR_P1,addr);
	uart_send_string("rx_addr_p1 = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(STATUS);
	uart_send_string("status reg = ");
	uart_send_integer(reg);
	uart_send_byte('\n');
	
	uart_print("***  END  ***");
}




void nrf_tx_data(volatile uint8_t byte)
{
	volatile uint8_t status = 0;
	
	// load byte in nrf tx fifo buffer
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	spi_rw_byte(W_TX_PAYLOAD);
	_delay_us(10);
	spi_rw_byte(byte);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
	
	// transmit via air
	NRF_CE_PULSE;
		
	// check if transmit success
	do
	{
		NRF_CSN_PIN_LOW;
		_delay_us(10);
		status = spi_rw_byte(_NOP);
		_delay_us(10);
		NRF_CSN_PIN_HIGH;
	}
	while(((status & (1<<TX_DS)) || (status & (1<<MAX_RT))) == 0);
	
	// clear flags
	nrf_w_reg(STATUS,(1<<TX_DS));
	nrf_w_reg(STATUS,(1<<MAX_RT));
	
	// give some time to settle for next transmission
	_delay_ms(10);
	
	// clear tx fifo buffer
	flush_tx();
}

uint8_t get_status(void)
{
	volatile uint8_t stat = 0;
	
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	stat = spi_rw_byte(_NOP);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
	
	return stat;
}

void flush_tx(void)
{
	nrf_send_cmd(FLUSH_TX);
}


void nrf_transmit_string(uint8_t *string)
{
	while(*string != '\0')
	{
		nrf_tx_data(*string);
		string += 1;
	}
}