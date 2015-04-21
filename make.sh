#!/usr/bin/env bash
OUTPUT_PATH=./bin/amnesia
SRC_PATH=./src

gcc $SRC_PATH/* -Wall -c -Iinclude -o $OUTPUT_PATH

echo "Compiled to $OUTPUT_PATH"
