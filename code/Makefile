CC=gcc -Wall -Wextra -std=c99
OUTPUT=bin/main
DIROBJ=obj
DIROBJLIB=lib/wsServer/src
DIRSRC=src
OBJ_FILES_LIST=$(DIROBJ)/main.o $(DIROBJ)/carte.o $(DIROBJ)/faction.o $(DIROBJ)/interface.o $(DIROBJ)/plateau.o $(DIROBJ)/structure.o $(DIROBJ)/test.o $(DIROBJ)/aleatoire.o $(DIROBJ)/effets.o $(DIROBJ)/position.o $(DIROBJ)/socket.o
OBJ_LIB_LIST=$(DIROBJLIB)/base64.o $(DIROBJLIB)/handshake.o $(DIROBJLIB)/sha1.o $(DIROBJLIB)/utf8.o $(DIROBJLIB)/ws.o
all: main
main: $(OBJ_FILES_LIST)
	$(CC) $^ $(OBJ_LIB_LIST) -o $(OUTPUT) -lcunit -lpthread
$(DIROBJ)/%.o: $(DIRSRC)/%.c
	$(CC) -o $@ -c $^
clean:
	rm -f $(DIROBJ)/*.o $(OUTPUT)


