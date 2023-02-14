#!/bin/bash

cd $(dirname $0)

for level in */; do
    for area in ${level}*/; do
        output=${level}$(basename $area).bgman
        
        echo "Generating $output:"
        for img in ${area}*.png; do
            convert ${img} -format "$area%f %@\n" \
                info:- ;
        done | ./gen_bg_manifest.py | tee $output
        
        echo ""
        echo "Trimming layers in ${area}"
        if test "$(which parallel 2> /dev/null )"; then
            echo "Found GNU Parallel"
            ls ${area}*.png | \
                parallel -P $(nproc) ./trim.sh
        else
            for img in ${area}*.png; do
                ./trim.sh $img
            done
        fi
    done
done

