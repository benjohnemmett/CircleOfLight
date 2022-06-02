F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = avr-stuff/util/uart/uart.o
INC = -I./avr-stuff/util/uart/

game.hex: game.o $(OBJS)
	$(CC) -mmcu=$(MCU) game.o $(OBJS) -o game.elf
	avr-objcopy -j .text -j .data -O ihex game.elf game.hex

game.o : game.cpp 
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ $(INC) -DF_CPU=$(F_CPU)

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash: game.hex
	avrdude -p $(MCU) -c usbasp -U flash:w:game.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex