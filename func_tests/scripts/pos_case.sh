#!/bin/bash

args=$(cat "$1")
./app.exe $args

if ./func_tests/scripts/comparator.sh ./out/temp.txt "$2"; then
    exit 0
else
    exit 1
fi
