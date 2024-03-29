# tool macros
CC = gcc
CLIBS = -lm -ldl -llua -lluajit-5.1 -lSDL2 -lSDL2_ttf
CERROR = -Wall
CFLAGS = $(CERROR) $(CLIBS) $(addprefix -I, $(HDR_PATH))
LFLAGS = $(CFLAGS) -c

# path macros
LIB_PATH := libs
HDR_PATH := include $(LIB_PATH)
BIN_PATH := bin

SRC_PATH := src
SRC_PATH += src/engine
SRC_PATH += src/api
SRC_PATH += $(LIB_PATH)/frozen

# compile macros
TARGET := $(BIN_PATH)/engine-runtime

# src files & obj files
SRC := $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ := $(patsubst %.c, $(BIN_PATH)/%.o, $(SRC))

# default rule
all: $(TARGET)

# non-phony targets
$(TARGET): $(OBJ)
	@if [ ! -d $(BIN_PATH) ]; then mkdir $(BIN_PATH); fi;
	@printf "%s:\n\t" $(notdir $(TARGET))
	@$(CC) $^ $(CFLAGS) -o $@
	@printf "Compiled Successfully!\n" 

$(BIN_PATH)/%.o: %.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;
	@printf "\t%-15s %-30s " $(notdir $^) $@
	@echo $(CLIBS)
	@$(CC) $(LFLAGS) -o $@ $^

.PHONY: clean
clean:
	@rm -rf $(BIN_PATH)
