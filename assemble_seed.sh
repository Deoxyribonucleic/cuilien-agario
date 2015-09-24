#!/bin/bash

# retarded sed hack below for newlines in cpp macros using $
cpp seeds/$1.asm | sed s/\\$/\\n/g > seed.asm

python cuilien-assembler/src/main.py seed.asm c
rm seed.asm

