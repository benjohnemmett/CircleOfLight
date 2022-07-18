F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

LOCAL_OBJS = LightController.o TestProgram.o ReflexProgram.o ButtonManager.o MenuProgram.o CountDownTimerProgram.o
OBJS = avr-stuff/util/uart/uart.o $(LOCAL_OBJS)
INC = -I./avr-stuff/util/uart/

main.hex: main.o $(OBJS)
	$(CC) -mmcu=$(MCU) main.o $(OBJS) -o main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.o : main.cpp $(LOCAL_OBJS)
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ $(INC) -DF_CPU=$(F_CPU)

%.o: %.cpp avr-stuff/util/uart/uart.o
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ $(INC) -DF_CPU=$(F_CPU)

.PHONY: flash
flash: main.hex
	avrdude -p $(MCU) -c usbasp -U flash:w:main.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex