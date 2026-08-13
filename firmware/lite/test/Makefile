# firmware/lite/test/Makefile — Lite 主机单测 (host gcc, 无需硬件/PlatformIO)
# 用法:  make test_<name>  # 单个单测编译并运行 (Task 2-4 逐步调用)
#        make run          # 全套 (三 bin 齐备后调用)
#        make clean
CC       ?= gcc
CFLAGS   ?= -std=c11 -Wall -Wextra -Werror -O2
# PlatformIO 的 LDF 会为 lib/ 各子目录自动加 -I; host 侧需手动逐个列出
CPPFLAGS += -I../lib/LSM6DSV16X -I../lib/Madgwick -I../lib/LiteSensorManager -I../../shared

# 每个 bin 声明其依赖源; 模式规则 %: %.c 用 $^ (全部前置源) 编译
test_lsm6dsv16x: test_lsm6dsv16x.c ../lib/LSM6DSV16X/lsm6dsv16x.c
test_madgwick: test_madgwick.c ../lib/Madgwick/madgwick.c
test_lite_sensor_manager: test_lite_sensor_manager.c \
	../lib/LiteSensorManager/lite_sensor_manager.c \
	../lib/LSM6DSV16X/lsm6dsv16x.c ../lib/Madgwick/madgwick.c \
	../../shared/hand_token.c ../../shared/hand_skeleton.c

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

run: test_lsm6dsv16x test_madgwick test_lite_sensor_manager
	@for b in test_lsm6dsv16x test_madgwick test_lite_sensor_manager; do \
	  echo "== $$b =="; ./$$b || exit 1; done

.PHONY: run clean
clean:
	rm -f test_lsm6dsv16x test_madgwick test_lite_sensor_manager
