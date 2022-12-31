#!/bin/bash

size="1868x1700+0+0"

echo "Preparing tutorial/cave backgrounds"

cd "$(dirname $0)"

for i in *.png; do
    echo "Cropping $i"

    in="tmp.png"
    out="tmp2.png"

    mv -- "$i" $in
    magick $in -crop "$size" $out
    rm $in
    mv -- $out "$i"
    echo
done
