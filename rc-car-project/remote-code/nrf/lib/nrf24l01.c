/*
 * nrf24l01.c
 *
 * Created: 27-09-2024 01:48:05
 *  Author: ksham
 */ 

#include "nrf24l01.h"


// send only cmd to nrf module
void nrf_send_cmd(volatile uint8_t cmd)
{
	volatile uint8_t status = 0;
	
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	status = spi_rw_byte(cmd);
	_delay_us(10);
	NRF_CSN_PIN_HIGH;
}

// write to nrf internal register
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

// read nrf internal register
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

// write rx address
void nrf_w_rx_addr(volatile uint8_t addr)
{
	NRF_CSN_PIN_LOW;
	_delay_us(10);
	
	addr = W_REGISTER | (addr & 0x1F);	// prepare write reg cmd
	
	spi_rw_byte(addr);
	_delay_us(10);
	
	//0x65646f4e31
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

// write tx address and it's rx pipe
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

// read 5 byte array value
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
	PORTD |= (1<<2);	//pull up
	DDRD &= ~(1<<2);	// input
	
	EICRA |= (1<<1);	// falling edge trigger
	EIMSK |= (1<<0);	// enable interrupt 0
	
	/*GPIO_DDR_MODE(NRF_IRQ_DDR,NRF_IRQ_PIN,INPUT);
	GPIO_PULLUP_ON(NRF_IRQ_PORT,NRF_IRQ_PIN);
	
	SET_INT_TRIG_LEVEL(FALLING_EDGE);
	
	ENABLE_INTERRUPT(EXT_INTERRUPT_REG,EXTERNAL_INTERRUPT_0);*/
}

// initialise nrf peripheral
void nrf_tx_init(void)
{	
	GPIO_DDR_MODE(NRF_CE_DDR,NRF_CE_PIN,OUTPUT);
	
	// initialise interrupt
	nrf_irq_init();
	
	// spi still works
	// ce low, no rx/tx
	NRF_CE_PIN_LOW;
	
	//csn high, no spi
	NRF_CSN_PIN_HIGH;
	
	_delay_ms(100);// power up module wait
	
	//enable auto ack on pipe 0 and 1
	nrf_w_reg(EN_AA,0x03);
	
	// wait 500+86us before next retry, retry 5 times
	nrf_w_reg(SETUP_RETR,0x85);
	
	// enable data pipe 0 and 1
	nrf_w_reg(EN_RXADDR,0x03);
	
	// pipe 0 for rx
	nrf_w_rx_addr(RX_ADDR_P0);
	
	// tx pipe 1 used 
	nrf_w_tx_addr(RX_ADDR_P1);
	nrf_w_tx_addr(TX_ADDR);
	
	// 1 byte payload set
	nrf_w_reg(RX_PW_P1,0x01);
	nrf_w_reg(RX_PW_P0,0x01);
	
	// transmit mode, irq enable, 2B crc on
	nrf_w_reg(CONFIG,0x0E);
	
	// clear all flags
	nrf_w_reg(STATUS,0x7E);
	
	// clear rx/tx buffers
	nrf_send_cmd(FLUSH_TX);
	nrf_send_cmd(FLUSH_RX);
	
	//wait
	_delay_ms(100);
	
}

// to print 5 bytes array value
void nrf_print_addr(volatile uint8_t* addr)
{
	volatile uint8_t i = 0;
	
	for(i = 0;i<5;i++)
	{
		print_dectohex(addr[i]);
	}
}

// print nrf internal 
void nrf_print_registers(void)
{
	volatile uint8_t reg = 0;
	volatile uint8_t addr[6] = {0};
	
	uart_print("***  NRF Internal Registes Configuration  ***");
	
	reg = nrf_r_reg(EN_AA);
	uart_send_string("en_aa = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(SETUP_RETR);
	uart_send_string("setup_retr = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(EN_RXADDR);
	uart_send_string("en_rxaddr = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(SETUP_AW);
	uart_send_string("setup_aw = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RF_CH);
	uart_send_string("rf_ch = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RF_SETUP);
	uart_send_string("rf_setup = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RX_PW_P0);
	uart_send_string("rx_pw_p0 = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(RX_PW_P1);
	uart_send_string("rx_pw_p1 = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(CONFIG);
	uart_send_string("config = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	nrf_r_addr(TX_ADDR,addr);
	uart_send_string("tx_addr_pipe1, lsb first = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	nrf_r_addr(RX_ADDR_P0,addr);
	uart_send_string("rx_addr_pipe0, lsb first = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	nrf_r_addr(RX_ADDR_P1,addr);
	uart_send_string("tx_receive_pipe1_addr, lsb first = ");
	nrf_print_addr(addr);
	uart_send_byte('\n');
	
	reg = nrf_r_reg(STATUS);
	uart_send_string("status flags reg = 0x");
	print_dectohex(reg);
	uart_send_byte('\n');
	
	uart_print("***  END  ***");
}



// transmit one byte via nrf
void nrf_tx_data(volatile uint8_t byte)
{
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
	
	// give some time to settle for next transmission
	_delay_ms(30);
	
	// clear tx fifo buffer
	flush_tx();
}

// get current status of nrf flags
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

// clear nrf tx fifo buffer
void flush_tx(void)
{
	nrf_send_cmd(FLUSH_TX);
}


// transmit strings via nrf
void nrf_transmit_string(uint8_t *string)
{
	while(*string != '\0')
	{
		nrf_tx_data(*string);
		string += 1;
	}
}