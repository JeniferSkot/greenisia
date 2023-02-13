#!/bin/bash
# Move maps from the temp to the base assets dir

echo ""

echo "Going to bin dir."
cd "$(dirname $(dirname $(pwd)/$0))"


if [ -d ./assets ]; then
    echo Found ./assets
else
    echo Could not find temporary assets dir.
    exit 0
fi

if [ -d ../assets ]; then
    echo Found ../assets
else
    echo Could not find main assets dir.
    exit 0
fi


mkdir -p assets/maps
mkdir -p ../assets/maps


cd assets/maps
for map in *.map; do
    echo "Checking $map" 
    real="../../../assets/maps/$map"
    if ! cmp -s "$map" "$real"; then
        echo "Updating $map"
        cp "$map" "$real"
    fi
done;

cd ../level_data
for lvl in *.lvl; do
    echo "Checking $lvl" 
    real="../../../assets/level_data/$lvl"
    if ! cmp -s "$lvl" "$real"; then
        echo "Updating $lvl"
        cp "$lvl" "$real"
    fi
done;

