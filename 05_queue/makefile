
CC := gcc

OUT_DIR := ./out
INC_DIR := ./inc
SRC_DIR := ./src
UNIT_TESTS_DIR := ./unit_tests

CFLAGS := -std=c99 -Wall -Wextra -Werror -Wpedantic -I $(INC_DIR)
CHECK_FLAGS := -lcheck #-lpthread -lrt -lm -lsubunit

# Получение переменных с файлами

CFILES := $(wildcard $(SRC_DIR)/*.c)

OBJFILES := $(CFILES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

UNIT_TESTS_CFILES := $(wildcard $(UNIT_TESTS_DIR)/*.c)

UNIT_TESTS_OBJFILES := $(UNIT_TESTS_CFILES:$(UNIT_TESTS_DIR)/%.c=$(OUT_DIR)/%.o)

TESTED_OBJFILES := $(filter-out $(OUT_DIR)/main.o, $(UNIT_TESTS_OBJFILES:$(OUT_DIR)/check_%.o=$(OUT_DIR)/%.o))

# Функции
app.exe: $(OUT_DIR) $(OBJFILES)
	$(CC) $(OBJFILES) -o $@ -lm

$(OUT_DIR):
	@mkdir -p $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT_DIR)/%.o: $(UNIT_TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: func stats clean mem_check png_graph
clean:
	rm -f $(OUT_DIR)/*

func: app.exe
	./func_tests/scripts/func_tests.sh

stats: app.exe
	./func_tests/scripts/stats.sh

mem_check: app.exe
	./func_tests/scripts/func_tests.sh -m
