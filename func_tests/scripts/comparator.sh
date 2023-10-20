#!/bin/bash

# byte-by-byte comparison.
if cmp -s $1 $2; then
    exit_mode=0
else
    exit_mode=1
fi

# Setting the exit code.
exit $exit_mode
