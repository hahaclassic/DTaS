#!/bin/bash
find . -name "*.exe" -type f -delete
find . -name "*.o" -type f -delete
find . -name "*.gcno" -type f -delete
find . -name "*.gcda" -type f -delete
find . -name "extra_file" -type f -delete
find . -name "result" -type f -delete
find . -name "*.info" -type f -delete

rm -r ./report
