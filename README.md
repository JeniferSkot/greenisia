A platformer game. (Work in progress)

# Building (Linux)

Requirements: SDL2, SDL2 IMG, SDL2 TTF, C++17-compatible compiler (i.e. GCC)

Requirements for generating assets: bash, imagemagick 7, python3, GNU parallel (optional)
Older versions of imagemagick work too, but we've used `magick` for everything
in the assets processing scripts, so you'd have to fix this. (Pull Request welcome)
Having GNU Parallel will speedup assets processing, but is not required.

You can build and run with:

    $ make -j $(nproc) run


## Emscripten

You have to setup and enter the Emscripten SDK environment.

To create an emscripten build use makefile\_ems

    $ make -f makefile_ems -j $(nproc)

After this serve the files in bin\_ems using an http server.

    $ cd bin_ems
    $ python -m http.server
