#!/bin/bash
port=1234

ncat -lp $port -ke ./FMS
