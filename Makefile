CPPFLAGS += -I/opt/homebrew/opt/libpq/include -I/opt/homebrew/Cellar/openssl@3/3.5.2/include

LDFLAGS += -L/opt/homebrew/opt/libpq/lib -lpq

SRC_DIR := src

SRCS := $(wildcard $(SRC_DIR)/*.c)

OBJS := $(SRCS:.c=.o)

TARGET := server

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc $(OBJS) -o $(TARGET) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $< -o $@ $(CPPFLAGS)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
