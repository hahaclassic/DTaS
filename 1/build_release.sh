#!/bin/bash
SRC_FILES=$(find . -maxdepth 1 -type f -name '*.c')
FLAGS="-std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla"

# Check if there're any source files
if [ -z "$SRC_FILES" ]; then
    echo "[ERR]: Directory doesn't contain any source files"
    exit 1
fi

# Compilation
for src_file in ${SRC_FILES}; do
    if ! gcc ${FLAGS} -c ${src_file}; then
        echo "[ERR]: project can't be compiled"
        exit 1
    fi
done

# Linking
OBJ_FILES=$(find . -maxdepth 1 -type f -name '*.o')
if ! gcc -o app.exe ${OBJ_FILES}; then
    echo "[ERR]: unable to link project"
    exit 1
fi
