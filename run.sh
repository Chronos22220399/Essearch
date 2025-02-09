#!/bin/fish

cmake -B build -DGumbo_static_LIBRARY=/usr/lib/libgumbo.so
cmake --build build
build/Arachne/Arachne
