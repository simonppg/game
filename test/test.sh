#!/bin/bash
gcc -g main.c utils_test.c ../utils.c -l cmocka -I.. -D TEST=1
./a.out
