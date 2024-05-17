
CC := gcc

OUT_DIR := ./out
INC_DIR := ./inc
SRC_DIR := ./src
UNIT_TESTS_DIR := ./unit_tests

CFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic -I $(INC_DIR)
CHECK_FLAGS := -lcheck #-lpthread -lrt -lm -lsubunit

# Получение переменных с файлами

CFILES := $(wildcard $(SRC_DIR)/*.c)

OBJFILES := $(CFILES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

UNIT_TESTS_CFILES := $(wildcard $(UNIT_TESTS_DIR)/*.c)

UNIT_TESTS_OBJFILES := $(UNIT_TESTS_CFILES:$(UNIT_TESTS_DIR)/%.c=$(OUT_DIR)/%.o)

TESTED_OBJFILES := $(filter-out $(OUT_DIR)/main.o, $(UNIT_TESTS_OBJFILES:$(OUT_DIR)/check_%.o=$(OUT_DIR)/%.o))

# Функции
app.exe: $(OUT_DIR) $(OBJFILES)
	$(CC) $(OBJFILES) -o $@

$(OUT_DIR):
	@mkdir -p $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

unit_tests.exe: $(OUT_DIR) $(UNIT_TESTS_OBJFILES) $(TESTED_OBJFILES) 
	$(CC) $(UNIT_TESTS_OBJFILES) $(TESTED_OBJFILES) -o $@ $(CHECK_FLAGS)

$(OUT_DIR)/%.o: $(UNIT_TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: func generate
clean:
	rm -f $(OUT_DIR)/*

generate:
	./generate_data.py
