#!/bin/bash

cd $(dirname $0)

for level in */; do
    for area in ${level}*/; do
        output=${level}$(basename $area).bgman
        
        echo "Generating $output:"
        magick ${area}*.png \
            -format "$area%f %@\n" \
            info:- | \
                ./gen_bg_manifest.py | tee $output
        
        echo ""
        echo "Trimming layers in ${area}"
        for img in ${area}*.png; do
            echo "Trimming $img"
            in=itmp.png
            out=otmp.png
            mv "$img" "$in"
            magick "$in" -trim "$out"
            rm "$in"
            mv "$out" "$img"
        done
    done
done

