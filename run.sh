#!/bin/fish

cmake -B build -G Ninja -DGumbo_static_LIBRARY=/usr/lib/libgumbo.so
ninja -C build
