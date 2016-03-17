CC=gcc
CFLAGS=-I../conf -std=c99 -lpthread

HEADERS = client_thread.h

DEPS = main.c client_thread.c conf.c

O = main.o client_thread.o conf.o
OBJ = $(patsubst %.o,$(BUILD_DIR)/client/%.o, $(O))

BUILD_DIR=../../build

.PHONY: default all clean format

default: $(BUILD_DIR)/tp2_client

all: default

format: $(DEPS)
	indent -gnu $(DEPS) $(HEADERS)
	rm -f *~

$(BUILD_DIR)/client/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/tp2_client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@echo "Cleaning build directory..."
	@rm -f $(BUILD_DIR)/client/*.o $(BUILD_DIR)/tp2_client
