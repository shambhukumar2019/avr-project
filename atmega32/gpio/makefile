TARGET = app
MCU = atmega16

SRC_PATH = src
LIB_PATH = lib
INC_PATH = include
TARGET_PATH = bin
BUILD_PATH = build

CC = avr-gcc
OBJCOPY = avr-objcopy
RM = rm

SRC_FILE = $(wildcard $(SRC_PATH)/*.c)
LIB_FILE = $(wildcard $(LIB_PATH)/*.c)
C_FILE = $(SRC_FILE) $(LIB_FILE)

ELF_FILE = $(BUILD_PATH)/$(TARGET).elf
HEX_FILE = $(TARGET_PATH)/$(TARGET).hex

CC_FLAGS = -Wall -Wextra -Os -mmcu=$(MCU)
INC_FLAGS = -I $(INC_PATH)
OBJCOPY_FLAGS = -O ihex -g
RM_FLAGS = -r -f



hex: $(HEX_FILE)

$(HEX_FILE): $(ELF_FILE)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $^ $@


elf: $(ELF_FILE)

$(ELF_FILE): $(C_FILE)
	$(CC) $(CC_FLAGS) $(INC_FLAGS) -o $@ $^


.PHONY: clean
clean:
	$(RM) $(RM_FLAGS) *.elf *.hex *.map *.s *.i *.o
