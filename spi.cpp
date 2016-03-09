#include "spi.h"

void spi_init(bool state) {
	//
	// configure state (default is slave)
	//
	if(state) {
#define SPI_STATE_MASTER
	}
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
#ifndef SPI_STATE_MASTER
		| _BV(USICS1)
#endif
		;

#define SPI_INIT
}

void spi_init(void) {
	spi_init(SPI_SLAVE);
}

uint8_t spi_wrrd(uint8_t out) {
#ifndef SPI_INIT
	//
	// TODO:
	// 	- remove return value
	// 	- add avr-gicc compiler warning
	//
	return 0x00;
#endif
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
#ifdef SPI_STATE_MASTER
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
#endif
	while ((USISR & _BV(USIOIF)) == 0);
	//
	// return shifted-in data
	//
	return USIDR;
}
