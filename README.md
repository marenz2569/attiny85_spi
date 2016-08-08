# ATTinyX5 SPI Library
This library was writen to give you a simple SPI implementation for the ATTiny's 25, 45 and 85.

## Usage
just include the `spi.h` file into your project.

### Initialitzation
	spi_init()

to change between spi master and slave mode comment out `#define SPI_MASTER` in `spi.h`.

### Sending and Receiving
To send or receive you can use the following function. It takes a uint8_t as an argument that will be send and returns the value that is received.

	uint8_t = spi_wrrd(uint8_t)

**Note:** you need to implement clock select yourself.
