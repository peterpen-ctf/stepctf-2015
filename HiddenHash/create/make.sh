#!/bin/sh

g++ -m32 -o hhsh.elf task.cpp
execstack -s hhsh.elf

