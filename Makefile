CC = gcc
CFLAGS = -Wextra -Wall -Werror -g
SRC = src/main.c
TARGET = lameboy

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lSDL2

.PHONY: clean
clean:
	rm -f $(TARGET)