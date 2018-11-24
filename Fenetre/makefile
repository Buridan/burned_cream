CFLAGS= -O3 -W -Wall -pedantic
LDFLAGS=-lSDL2
EXE=$(TARGET_DIR)fenetre
TARGET_DIR=./target/
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

#executables
RM:= rm
MD:= mkdir
CC:= gcc

#rules

all:$(TARGET_DIR) $(EXE)

$(TARGET_DIR):
	@$(MD) -p $(TARGET_DIR)

$(EXE): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o:%c
	@$(CC) $(CFLAGS)-o $@ -c $< 

.PHONY: clean mrproper

clean:
	@$(RM) -rf *.o
mrproper: clean
	@$(RM) -rf $(EXE) $(TARGET_DIR)
