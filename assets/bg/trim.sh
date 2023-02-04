#!/bin/bash

if [ $# -ne 1 ]; then
    echo "This script needs one argument: image path"
    exit
fi

echo "Trimming $1"

tmp=${1}.tmp
mv $1 $tmp
magick $tmp -trim $1
rm $tmp

