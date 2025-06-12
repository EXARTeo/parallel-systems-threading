# Variables
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread
TARGET = main
SRCS = ../parallel-systems-handout-1-winter-2024-25-helpcode/my_rand.c main.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Valgrind rule
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Phony targets
.PHONY: all clean valgrind
