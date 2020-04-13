###############################################################################
# Main application file name
###############################################################################
TARGET = $(notdir $(shell pwd))


###############################################################################
# Build path
###############################################################################
ifeq ($(DEBUG), 1)
BUILD_DIR := build/debug
else
BUILD_DIR := build/release
endif


###############################################################################
# Source
###############################################################################
# Defines
C_DEFINES := STM32G431xx
C_DEFINES += PREFETCH_ENABLE=0
C_DEFINES += INSTRUCTION_CACHE_ENABLE=1
C_DEFINES += DATA_CACHE_ENABLE=1
C_DEFINES += HSE_VALUE=24000000


# C includes
INCLUDES:= $(shell find code -type d)

# ASM sources
A_SOURCES := $(wildcard $(addsuffix /*.s, $(INCLUDES)))

# C sources
C_SOURCES := $(wildcard $(addsuffix /*.c, $(INCLUDES)))


###############################################################################
# Compilers and Utilities binaries
###############################################################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path (default: current folder)
ifndef GCC_PATH
GCC_PATH:= C:/toolchain/gcc-arm-none-eabi-9-2019-q4-major/bin/
endif
AS 		:= $(GCC_PATH)/$(PREFIX)gcc -xassembler-with-cpp
CC 		:= $(GCC_PATH)/$(PREFIX)gcc
OBJCOPY := $(GCC_PATH)/$(PREFIX)objcopy
OBJDUMP := $(GCC_PATH)/$(PREFIX)objdump
SZ 		:= $(GCC_PATH)/$(PREFIX)size


###############################################################################
# CFLAGS
###############################################################################
# CPU
CPU := -mcpu=cortex-m4

# FPU
FPU := -mfloat-abi=hard -mfpu=fpv4-sp-d16

# MCU
MCU := $(CPU) -mthumb $(FPU)

# Optimization and Debug level
ifeq ($(DEBUG), 1)
OPT := -Og -g -gdwarf-2
else
OPT := -Os
endif

# Compile gcc flags
FLAGS := $(OPT) $(MCU)
FLAGS += -ffunction-sections
FLAGS += -fdata-sections
FLAGS += -fshort-enums
FLAGS += -funsigned-char
FLAGS += -fshort-wchar

# FLAGS += -fpack-struct
FLAGS += -std=gnu11
FLAGS += -flto
FLAGS += -Winline -Wall -Wextra -Wpedantic #-Werror 

AFLAGS := $(FLAGS)

CFLAGS := $(FLAGS)
CFLAGS += -MMD -MP
CFLAGS += $(addprefix -D, $(C_DEFINES)) $(addprefix -I, $(INCLUDES)) 

###############################################################################
# LFLAGS
###############################################################################
# link script
LSCRIPT := STM32G431RBTx_FLASH.ld

# libraries
LIBS := -lc -lm -lnosys 
LIBDIR := 
LFLAGS := $(MCU) -T$(LSCRIPT) $(LIBDIR) $(LIBS)
LFLAGS += -specs=nano.specs 
# LFLAGS += -u _scanf_float 
# LFLAGS += -u _printf_float
LFLAGS += -Wl,--gc-sections
LFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref 


###############################################################################
# HFLAGS
###############################################################################
# Options for HEX file generation
HFLAGS := -O ihex


###############################################################################
# build the application
###############################################################################
# list of objects
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/, $(notdir $(A_SOURCES:.s=.o)))
vpath %.c $(sort $(INCLUDES))
vpath %.s $(sort $(INCLUDES))

# Build all
all: info $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).lss
	@echo
	$(SZ) $(BUILD_DIR)/$(TARGET).elf -G
	@echo
	@echo $(BUILD_DIR)/$(TARGET).lss

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile	
	$(CC) $(OBJECTS) $(LFLAGS) -o $@
	
	
$(BUILD_DIR)/%.lss: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJDUMP) -S $< > $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) $(HFLAGS) $< $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo $<
	$(CC) -c $(CFLAGS) $< -o $@	

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo $<
	$(AS) -c $(AFLAGS) $< -o $@
	 
$(BUILD_DIR):
	mkdir -p $@

###############################################################################
# clean up
###############################################################################
.PHONY: clean
clean:
	@echo -rm -fR $(dir $(BUILD_DIR))
	-rm -fR $(dir $(BUILD_DIR))

###############################################################################
# Flash
###############################################################################
.PHONY: flash
flash : 	
	$(AVRDUDE) $(DUDEFLAGS)

###############################################################################
# Info
###############################################################################
info:
	@echo -e "\033[32;1;40m""Compiler version:""\033[0m"
	$(CC) --version
	@echo -e "\033[32;1;40m""Compile flags:""\033[0m" $(FLAGS)
	@echo -e "\033[32;1;40m""Linking flags:""\033[0m" $(LFLAGS)
	@echo
	# @echo $(OBJECTS)
	# @echo 

.PHONY: test
test : 	
	@echo ${A_SOURCES}
###############################################################################
# dependencies
###############################################################################
-include $(wildcard $(BUILD_DIR)/*.d)
###############################################################################