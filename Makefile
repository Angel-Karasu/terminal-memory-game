CC = gcc
CFLAGS = -Wall -Wextra
EXEC = memory
SRC=$(shell find . -name '*.c')
OBJ=$(patsubst %.c, %.o, $(SRC))

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)
