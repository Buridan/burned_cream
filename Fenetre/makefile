CFLAGS= -O3 -W -Wall -pedantic
LDFLAGS=-lSDL2
EXE=$(TARGET_DIR)fenetre
TARGET_DIR=./target/
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
OBJ_DIR=./obj/

#executables
RM:= rm
MD:= mkdir
CC:= gcc

#rules

all:$(TARGET_DIR) $(OBJ_DIR) $(EXE)

$(TARGET_DIR):
	@$(MD) -p $(TARGET_DIR)

$(OBJ_DIR):
	@$(MD) -p $(OBJ_DIR)

$(EXE): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)$^ $(LDFLAGS)

$(OBJ_DIR)%.o:%c
	@$(CC) $(CFLAGS)-o $(OBJ_DIR)$@ -c $< 

.PHONY: clean mrproper

clean:
	@$(RM) -rf *.o
mrproper: clean
	@$(RM) -rf $(EXE) $(TARGET_DIR)
