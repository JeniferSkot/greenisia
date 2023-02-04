#!/usr/bin/python

# Finds the area of a composite image and
#  calculates the relative areas of its layers.
# The output is meant for use in the background system.

# As output, first line contains the composite image size
# Every next line contains "${path} ${size}" pair.
# Sizes are formatted in magick's default format:
# ${width}x${height}+${offset_x}+${offset_y}

import sys

layers = []
final_area = None

for line in sys.stdin:
    line = line.replace("\n", "")
    file = line.split(' ')[0]
    area = line.split(' ')[1]

    w = int(area.split('x')[0])
    other = area.split('x')[1].split('+')
    h = int(other[0])
    x = int(other[1])
    y = int(other[2])

    layers.append([file, w, h, x, y])

    if final_area == None:
        final_area = [w+x, h+y, x, y]
    else:
        if final_area[0] < w+x:
            final_area[0] = w+x
        if final_area[1] < h+y:
            final_area[1] = h+y
        if final_area[2] > x:
            final_area[2] = x
        if final_area[3] > y:
            final_area[3] = y

final_area[0] -= final_area[2]
final_area[1] -= final_area[3]

print(f"{final_area[0]}x{final_area[1]}"
      + f"+{final_area[2]}+{final_area[3]}")

#layers.sort(key = lambda l : l[0])

for layer in layers:
    name = layer[0]
    w = layer[1]
    h = layer[2]
    x = layer[3] - final_area[2]
    y = layer[4] - final_area[3]
    size = f"{w}x{h}+{x}+{y}"
    print(name + " " + size)

