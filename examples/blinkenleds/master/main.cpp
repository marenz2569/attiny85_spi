#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define F_CPU 8000000L

static void init(void);
static void spi_init(void);
static uint8_t spi_wrrd(uint8_t out);

int main(void) {
	//
	// init MCU
	//
	init();
	
	for(;;) {
		spi_wrrd(0xcc);
		_delay_ms(1000);
		spi_wrrd(0xdd);
		_delay_ms(1000);
	}
	return 0;
}

static void init(void) {
	//
	// init spi
	//
	spi_init();
}

static void spi_init(void) {
	//
	// output:
	//	DO
	//	USCK
	//
	DDRB |= _BV(DDB1) | _BV(DDB2);
	//
	// spi mode:
	// 	three wire
	//
	USICR |= _BV(USIWM0)
		;
}

static uint8_t spi_wrrd(uint8_t out) {
	//
	// write data to register
	//
	USIDR = out;
	//
	// reset USIOIF flag
	//
	USISR = _BV(USIOIF);
	//
	// wait for counter buffer overflow
	//
	do
		//
		// spi mode:
		// 	three wire
		//
		// clock source:
		// 	external, rising
		// 4-bit counter cs:
		// 	usitc
		//
		// clock
		//
		USICR = _BV(USIWM0)
			| _BV(USICS1) | _BV(USICLK)
			| _BV(USITC)
			;
	while ((USISR & _BV(USIOIF)) == 0);
	//
	// return data from slave
	//
	return USIDR;
}
