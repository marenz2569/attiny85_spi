# ATTinyX5 SPI Library
This library was writen to give you a simple SPI implementation for the ATTiny's 25, 45 and 85.

## Usage
just include the `spi.h` file into your project.

## Functions
All the function are in a namespace called `spi`. You can either use all the functions with `using namespace spi` or you can only a particular one by writting `spi::` in front of the function name.

### Initialitzation
	spi_init(MODUS)
	MODUS := SPI_SLAVE | SPI_MASTER

### sending and receiving
To send or receive you can use the following function. It takes a uint8_t as an argument that will be send and returns the value that is received.

	uint8_t = spi_wrrd(uint8_t)

The library also defines `spi_rd()` as `spi_wrrd(0x00)`.
