CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = Main.c StrList.c
OBJS = $(SRCS:.c=.o)
EXEC = StrList

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -f *.o $(EXEC)

run: $(EXEC)
	./$(EXEC)
