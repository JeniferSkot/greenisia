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
    if ! cmp -s "$map" "../../../assets/maps/$map"; then
        echo "Updating $map"
        cp "$map" "../../../assets/maps/$map"
    fi
done;

cd ../level_data
for lvl in *.lvl; do
    echo "Checking $lvl" 
    if ! cmp -s "$lvl" "../../../assets/maps/$lvl"; then
        echo "Updating $lvl"
        cp "$lvl" "../../../assets/maps/$lvl"
    fi
done;

