#!/bin/bash

gcc -g ../src/main.c ../src/headers/network.h ../src/sources/network.c ../src/headers/comman.h ../src/sources/comman.c -lpthread 
