#!/bin/bash

SIZES="1 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000"

mkdir -p ./apps

c_files=$(ls ./c_files/*.c)

for c_file in $c_files; do
    filename=$(basename "$c_file" .c)
    mkdir -p "./apps/${filename}"
    for size in $SIZES; do
        gcc -std=c99 -O0 "$c_file" -o "./apps/${filename}/size_${size}.exe" -lm -DNMAX="$size"
    done
done
