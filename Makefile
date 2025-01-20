CC = gcc
CFLAGS = -Wextra -Wall -g
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = lameboy

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

graphics: $(SRC_DIR)/graphics/graphics.c
	$(CC) $(CFLAGS) -o graphics $(SRC_DIR)/graphics/graphics.c -lSDL2


.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
