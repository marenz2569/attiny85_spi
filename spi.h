#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __SPI_H
#define __SPI_H

#define SPI_MASTER	true
#define SPI_SLAVE	false

	/*
	 * initializes three wire spi ports:
	 * 	PB0
	 * 	PB1
	 * 	PB2
	 * arguments:
	 * 	none:
	 * 		sets the spibus to slave mode
	 * 	bool:
	 * 		set to true for master mode (SPI_MASTER)
	 * 		or false (SPI_SLAVE) for slave mode
	 */
	void spi_init(bool);
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
	uint8_t spi_wrrd(uint8_t);

#define spi_rd()	spi_wrrd(0x00)

#endif
