#include "spi.h"

void spi_init(void) {
	/*
	 * output:
	 *	DO
	 *	USCK
	 *		- only on master mode
	 */
	DDRB |= _BV(DDB1);
#ifdef SPI_MASTER
	DDRB |= _BV(DDB2);
#endif
	/*
	 * spi mode:
	 * 	three wire
	 * external clock:
	 * 	- only on slave mode
	 */
	USICR |= _BV(USIWM0);
#ifndef SPI_MASTER
	USICR |= _BV(USICS1);
#endif
}

uint8_t spi_wrrd(uint8_t out) {
	/*
	 * write data to register
	 */
	USIDR = out;
	/*
	 * reset USIOIF flag
	 */
	USISR = _BV(USIOIF);
	/*
	 * wait for counter buffer overflow
	 */
		
	do
#ifdef SPI_MASTER
			/*
			 * spi mode:
			 * 	three wire
			 *
			 * clock source:
			 * 	external, rising
			 * 4-bit counter cs:
			 * 	usitc
			 *
			 * clock
			 */
			USICR = _BV(USIWM0)
			      | _BV(USICS1) | _BV(USICLK)
			      | _BV(USITC);
#endif
	while ((USISR & _BV(USIOIF)) == 0);
	/*
	 * return shifted-in data
	 */
	return USIDR;
}
