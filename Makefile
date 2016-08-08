DEVICE     = attiny85
CLOCK      = 8000000
OBJECTS    = src/spi.o

COMPILE = avr-gcc -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -fno-exceptions

all:	$(OBJECTS)

%.o:	%.c
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJECTS)
