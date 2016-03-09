#include <avr/io.h>

#include "../../../spi.h"

void init(void);

int main(void) {
	//
	// init MCU
	//
	init();
	
	uint8_t val;
	for(;;) {
		val = spi_rd();
		if(val == 0xcc) {
			PORTB &= ~_BV(PORTB3);
			PORTB |= _BV(PORTB4);
		} else if(val == 0xdd) {
			PORTB &= ~_BV(PORTB4);
			PORTB |= _BV(PORTB3);
		}
	}
	return 0;
}

void init(void) {
	DDRB |= _BV(DDB4) | _BV(DDB3);	
	//
	// init spi
	//
	spi_init(SPI_SLAVE);
}
