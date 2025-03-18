#!/bin/bash
gcc $(pkg-config --cflags gtk+-3.0) -o virtual_diary virtual_diary.c $(pkg-config --libs gtk+-3.0)
