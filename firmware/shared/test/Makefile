# firmware/shared/test/Makefile — Hand Token + HKVT-M3A 主机单测 (host gcc, 无需硬件)
# 用法:  make            # 编译并运行全部
#        make test_hand_token
#        make test_hkvt_m3a
#        make clean
CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -Werror -O2 -I..

.PHONY: all run clean
all: run

test_hand_token: test_hand_token.c ../hand_token.c ../hand_skeleton.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_hkvt_m3a: test_hkvt_m3a.c ../hkvt_m3a.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

run: test_hand_token test_hkvt_m3a
	@for b in test_hand_token test_hkvt_m3a; do \
	  echo "== $$b =="; ./$$b || exit 1; done

clean:
	rm -f test_hand_token test_hkvt_m3a
