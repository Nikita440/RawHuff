# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Source and object files for main program
SRCDIR = builder
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Decoder
DECODER_DIR = decoder
DECODER_SRCS = $(wildcard $(DECODER_DIR)/*.c)
DECODER_OBJS = $(patsubst %.c,%.o,$(DECODER_SRCS))

# Targets
TARGET = encode_program
DECODER_TARGET = decode_program

# Default build
all: $(TARGET) $(DECODER_TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(DECODER_TARGET): $(DECODER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(DECODER_OBJS)

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(SRCDIR)/*.o $(DECODER_DIR)/*.o $(TARGET) $(DECODER_TARGET)

.PHONY: all clean
