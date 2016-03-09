#include <avr/io.h>
#include <stdint.h>

static void init(void);
static void spi_init(void);
static uint8_t spi_wrrd(uint8_t out);

#define spi_rd()	spi_wrrd(0x00)

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

static void init(void) {
	DDRB |= _BV(DDB4) | _BV(DDB3);	
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
	DDRB |= _BV(DDB1) | _BV(DDB2)
		;
	//
	// spi mode:
	// 	three wire
	//
	// clock source:
	// 	external rising
	// 4-bit counter cs:
	// 	external both
	//
	USICR |= _BV(USIWM0)
		| _BV(USICS1)
		;
}

static uint8_t spi_wrrd(uint8_t out) {
	//
	// write data to be sent to master
	//
	USIDR = out;
	//
	// clear counter overflow flag
	//
	USISR = _BV(USIOIF);
	//
	// wait for counter buffer overflow
	//
	while ((USISR & _BV(USIOIF)) == 0)
		;
	//
	// return data from master
	//
	return USIDR;
}
