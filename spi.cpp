#include "spi.h"

namespace spi {
	bool spi_state;

	void spi_init(bool input_state) {
		//
		// configure state
		//
		spi_state = input_state;
		//
		// output:
		//	DO
		//	USCK
		//		- only on master mode
		//
		DDRB |= _BV(DDB1);
		if(spi_state) DDRB |= _BV(DDB2);
		//
		// spi mode:
		// 	three wire
		// external clock:
		// 	- only on slave mode
		//
		USICR |= _BV(USIWM0);
		if(!spi_state) USICR |= _BV(USICS1);
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
			if(spi_state) {
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

}
