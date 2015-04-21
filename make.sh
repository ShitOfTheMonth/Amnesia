#!/usr/bin/env bash
OUTPUT_PATH=./bin/amnesia
SRC_PATH=./src

gcc -Wall -c -Iinclude -o $OUTPUT_PATH $SRC_PATH/*

echo "Compiled to $OUTPUT_PATH"
