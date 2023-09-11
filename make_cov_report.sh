#!/bin/bash
SRC_FILES=$(find . -maxdepth 1 -type f -name '*.c')
FLAGS="--coverage -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla"

# Check if there're any source files
if [ -z "$SRC_FILES" ]; then
    echo "[ERR]: Directory doesn't contain any source files"
    exit 1
fi

# Compilation
for src_file in ${SRC_FILES}; do
    if ! gcc "${FLAGS}" "${src_file}" -o app.exe; then
        echo "[ERR]: project can't be compiled"
        exit 1
    fi
done


./app.exe "$1" "$2" "$3"

lcov -t "COVERAGE" -o cov.info -c -d .

genhtml -o report cov.info
