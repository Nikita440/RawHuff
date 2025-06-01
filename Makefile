# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Source and object files for main program
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Source and object files for decoder program
DECODER_DIR = decoder
DECODER_SRCS = $(wildcard $(DECODER_DIR)/*.c)
DECODER_OBJS = $(DECODER_SRCS:.c=.o)

# Output executables
TARGET = my_program
DECODER_TARGET = decoder_program

# Default rule builds both programs
all: $(TARGET) $(DECODER_TARGET)

# Link object files into the main executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Link decoder object files into the decoder executable
$(DECODER_TARGET): $(DECODER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(DECODER_OBJS)

# Compile .c files into .o files for main program
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .c files into .o files for decoder program
$(DECODER_DIR)/%.o: $(DECODER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(SRCDIR)/*.o $(DECODER_DIR)/*.o $(TARGET) $(DECODER_TARGET)

.PHONY: all clean
