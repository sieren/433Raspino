#!/bin/bash

# Usage sendscript.sh systemCode unitCode command
# command 0 = off, 1 = on
#

str="$*"
echo "$str" > /dev/ttyACM0
