CC=gcc -Wall -Wextra -std=c99
OUTPUT=bin/main
DIROBJ=obj
DIRSRC=src
OBJ_FILES_LIST=$(DIROBJ)/main.o $(DIROBJ)/carte.o $(DIROBJ)/faction.o $(DIROBJ)/interface.o $(DIROBJ)/plateau.o $(DIROBJ)/structure.o
all: main
main: $(OBJ_FILES_LIST)
	$(CC) $^ -o $(OUTPUT)
$(DIROBJ)/%.o: $(DIRSRC)/%.c
	$(CC) -o $@ -c $^
clean:
	rm -f $(DIROBJ)/*.o $(OUTPUT)