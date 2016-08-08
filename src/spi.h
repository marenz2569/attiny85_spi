#include <avr/io.h>
#include <stdint.h>

#ifndef SPI_H__
#define SPI_H__

	/*
	 * comment out this definition to change to slave mode
	 */
	#define SPI_MASTER

	/*
	 * initializes three wire spi ports:
	 * 	PB0
	 * 	PB1
	 * 	PB2
	 * arguments:
	 * 	bool:
	 * 		set to true for master mode (SPI_MASTER)
	 * 		or false (SPI_SLAVE) for slave mode
	 */
	void spi_init(void);

	/*
	 * arguments:
	 * 	uint8_t:
	 * 		the value to be send to the spibus
	 * returns:
	 * 	always 0x00:
	 * 		if there was no initialization
	 * 		or if MCU did not receive anything
	 * 	any other value:
	 * 		if MCU did receive anything
	 */
	uint8_t spi_wrrd(uint8_t out);

#endif
