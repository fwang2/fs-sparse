#!/bin/bash

echo "create sparse.dat"
dd if=/dev/urandom bs=4096 count=2 of=sparse.dat

# hole from byte 8192 to byte 28671
dd if=/dev/urandom bs=4096 seek=7 count=2 of=sparse.dat

# let's create another hole
dd if=/dev/urandom bs=4096 seek=10 count=1 of=sparse.dat

echo "create normal.dat"
dd if=/dev/urandom bs=4096 count=2 of=normal.dat
