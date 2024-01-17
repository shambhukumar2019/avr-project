TARGET = main
MCU = atmega16

CC = avr-gcc
OBJCOPY = avr-objcopy
RM = rm

CODES = $(wildcard *.c)
SRC_FILE = src/$(CODES)
LIB_FILE = lib/$(CODES)

C_FILE = $(SRC_FILE) $(LIB_FILE)

#C_FILE = $(foreach var,$(SRC_LIST),$(var).c)
INC_FILE = include
ELF_FILE = build/$(TARGET)
HEX_FILE = bin/$(TARGET)

CC_FLAGS = -Wall -Wextra -Os -mmcu=$(MCU)
INC_FLAGS = -I $(INC_FILE)
OBJCOPY_FLAGS = -O ihex -g
RM_FLAGS = -r -f



hex: $(HEX_FILE).hex

$(HEX_FILE).hex: $(ELF_FILE).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $^ $@


elf: $(ELF_FILE).elf

$(ELF_FILE).elf: $(C_FILE)
	$(CC) $(CC_FLAGS) $(INC_FLAGS) -o $@ $^


.PHONY: clean
clean:
	$(RM) $(RM_FLAGS) $(ELF_FILE).elf $(HEX_FILE).hex
