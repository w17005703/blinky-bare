#Fernando Luiz Cola
#25/09/2015
#
# Modified by DK - 11-07-2018

#Toolchain and Path Configuration
TOOLCHAIN=~/.local/packages/gcc-arm/bin
PREFIX=$(TOOLCHAIN)/arm-none-eabi-
CC=$(PREFIX)gcc
LD=$(PREFIX)gcc
OBJCOPY=$(PREFIX)objcopy
SIZE=$(PREFIX)size
RM=rm -f

#Files Location
SRC=$(wildcard *.c)
OBJ=$(patsubst  %.c, %.o, $(SRC) )
ASSRC=$(wildcard *.S)
ASOBJ=$(patsubst  %.S, %.o, $(ASSRC) )

#GNU ARM GCC Configuration and Platform configurations
ARCHFLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mfpu=fpv4-sp-d16
INCLUDE=-I./includes/
CFLAGS= -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 \
	 -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs
LDFLAGS= $(ARCHFLAGS) -T "MK64FN1M0xxx12_flash.ld" -L"./" -Wl,-Map,blinky-bare.map

#Makefile rules
all: blinky-bare.elf blinky-bare.bin size

blinky-bare.elf: $(OBJ) $(ASOBJ)
	@echo '### Linking files ###'
	$(LD) $(LDFLAGS) $(CFLAGS) $(OBJ) $(ASOBJ) -o $@
blinky-bare.bin: blinky-bare.elf
	@echo 'Binary'
	$(OBJCOPY) -O binary $< $@
size:
	@echo "---- RAM/Flash Usage ----"
	$(SIZE) blinky-bare.elf

#Compiling each source file
%.o: %.c 
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) $(INCLUDE) -o $@ $<
%.o: %.S
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) $(INCLUDE) -o $@ $<

# Cleaning up
clean:
	$(RM) blinky-bare.elf blinky-bare.bin blinky-bare.map $(OBJ) $(ASOBJ)

