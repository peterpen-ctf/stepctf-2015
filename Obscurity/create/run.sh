#!/usr/bin/env bash
tag_port=3456
reader_port=6543

# Для завершения потомков по Ctrl+C
trap 'jobs -p | xargs kill -s 15' EXIT

make tag reader || exit 1
./service.py $tag_port ./tag &
./service.py $reader_port ./reader &
wait
