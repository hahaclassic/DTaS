#!/bin/bash


args=$(cat "$1")

if ! ./app.exe $args; then
    exit 0
else
    exit 1
fi
