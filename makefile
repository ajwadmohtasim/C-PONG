# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Libraries for Linux
LINUX_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Libraries for Windows
WINDOWS_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Source files
SRC = main.c game.c savedata.c screen.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = pong

# Detect the operating system
ifeq ($(OS),Windows_NT)
    # Windows specific settings
    LIBS = $(WINDOWS_LIBS)
    RM = del
    TARGET_EXT = .exe
else
    # Linux specific settings
    LIBS = $(LINUX_LIBS)
    RM = rm -f
    TARGET_EXT =
endif

# Default target
all: $(TARGET)$(TARGET_EXT)

# Rule to create the executable
$(TARGET)$(TARGET_EXT): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
	@$(RM) $(OBJ)

# Rule to create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean

# Rule to clean the directory
clean:
	@$(RM) $(TARGET)$(TARGET_EXT) $(OBJ) *.data
