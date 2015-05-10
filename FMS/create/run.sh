#!/bin/bash
su -c '/bin/echo 0 > /proc/sys/kernel/randomize_va_space'
port=1234

make main
ncat -lp $port -ke ./main