#!/bin/bash

base=$(dirname $(dirname "$(pwd)/$0"))
bin=$base/bin_ems
files="${bin}/game.data ${bin}/game.js ${bin}/game.wasm ${bin}/index.html"
server=davros
target_dir=/workspace/www/platformer_02/

scp $files ${server}:${target_dir}


