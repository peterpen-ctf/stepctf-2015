#!/bin/bash
/bin/echo 0 > /proc/sys/kernel/randomize_va_space
port=1234

ncat -lp $port -ke ./FMS
