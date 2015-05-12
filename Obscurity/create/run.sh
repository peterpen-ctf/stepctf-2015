#!/usr/bin/env bash
tag_port=3456
reader_port=6543

# Для завершения потомков по Ctrl+C
trap 'jobs -p | xargs kill -s 15' EXIT

ncat -lp $tag_port -k -e ./tag &
ncat -lp $reader_port -k -e ./reader &
wait
