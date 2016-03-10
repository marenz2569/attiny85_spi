#include "spi.h"

void spi_init(bool input_state) {
	//
	// configure state
	//
	state = input_state;
	//
	// output:
	//	DO
	//	USCK
	//		- only on master mode
	//
	DDRB |= _BV(DDB1);
	if(state) DDRB |= _BV(DDB2);
	//
	// spi mode:
	// 	three wire
	// external clock:
	// 	- only on slave mode
	//
	USICR |= _BV(USIWM0);
	if(!state) USICR |= _BV(USICS1);
}

uint8_t spi_wrrd(uint8_t out) {
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
		if(state) {
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
		}
	while ((USISR & _BV(USIOIF)) == 0);
	//
	// return shifted-in data
	//
	return USIDR;
}
