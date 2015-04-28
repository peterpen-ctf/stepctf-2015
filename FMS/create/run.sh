#!/bin/bash

port=1234

make main
ncat -lp $port -ke ./main