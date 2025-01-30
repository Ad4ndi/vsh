#!/bin/bash

mkdir -p lib

MODULES=()

while [[ $# -gt 0 ]]; do
    case "$1" in
        -l)
            shift
            while [[ $# -gt 0 ]] && [[ "$1" != -* ]]; do
                MODULES+=("$1")
                shift
            done
            ;;
        *)
            echo "Invalid argument: $1"
            exit 1
            ;;
    esac
done

nasm -f elf32 config.asm -o config.o
gcc -m32 -c src/main.c -o main.o
gcc -m32 -c src/color.c -o color.o
gcc -m32 -c src/prompt.c -o prompt.o

for module in "${MODULES[@]}"; do
    m_name=$(basename "$module" .c)
    gcc -m32 -fPIC -shared -o "lib/lib${m_name}.so" "$module"
done

gcc -m32 main.o config.o prompt.o color.o -ldl -o nsh 

rm -f *.o
echo "OK"
