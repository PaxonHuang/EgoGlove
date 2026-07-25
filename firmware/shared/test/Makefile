# firmware/shared/test/Makefile — Hand Token 主机单测 (host gcc, 无需硬件/PlatformIO)
# 用法:  make        # 编译并运行
#        make clean
CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -Werror -O2
BIN      = test_hand_token
SRC      = test_hand_token.c ../hand_token.c

.PHONY: all run clean
all: run

$(BIN): $(SRC) ../hand_token.h
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lm

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
