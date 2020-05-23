TARGET = libslist

CC = gcc
CFLAGS = -c -Iinclude -Wall -Wextra -pedantic -Werror

# Enable debug do         : make DEBUG=1
DEBUG ?= 0
INFO ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2
endif
# Enable info messages do : make INFO=1
ifeq ($(INFO) , 1)
	CFLAGS += -DINFO
endif

SRC_DIR_PATH = src

SOURCES = $(wildcard $(SRC_DIR_PATH)/*.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(SOURCES) $(TARGET)

static: $(SOURCES) $(OBJECTS)
	@ar rsv $(TARGET).a $(OBJECTS)

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.c
	@echo "  CC    $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(TARGET) *.a

