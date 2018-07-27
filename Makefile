SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

# Configuration for the current AN
LIBS=-larsal -larnetwork -larcommands -lardiscovery -larnetworkal -ljson
OUT=BebopDroneStartStream


all: $(OUT)

$(OUT): check_env $(OBJ)
	@gcc -o $@ -L$(ARSDK_ROOT)/out/arsdk-native/staging/usr/lib $(OBJ) $(LIBS)

%.o : %.c
	@gcc -o $@ -I$(ARSDK_ROOT)/out/arsdk-native/staging/usr/include $< -c

run : $(OUT)
	@env LD_LIBRARY_PATH=$(ARSDK_ROOT)/out/arsdk-native/staging/usr/lib ./$(OUT)

check_env:
ifndef ARSDK_ROOT
	$(error ARSDK_ROOT not defined. Please define it to the root folder of the SDK before calling this makefile)
endif

clean:
	@rm -f $(OUT) $(OBJ)

