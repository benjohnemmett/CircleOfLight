F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = avr-stuff/util/uart/uart.o LightController.o ReflexProgram.o ButtonManager.o
INC = -I./avr-stuff/util/uart/

main.hex: main.o $(OBJS)
	$(CC) -mmcu=$(MCU) main.o $(OBJS) -o main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.o : main.cpp LightController.o ReflexProgram.o ButtonManager.o
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ $(INC) -DF_CPU=$(F_CPU)

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash: main.hex
	avrdude -p $(MCU) -c usbasp -U flash:w:main.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex