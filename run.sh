#!/bin/bash

g++ \
    -lSDL2 \
    -lSDL2_image \
    -Wall -Wextra \
    src/*.cpp -o game \
    && ./game
