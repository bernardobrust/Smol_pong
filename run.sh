#!/bin/bash

# Quick testing on linux
meson compile --ninja-args=-t,compdb>compile_commands.json -C build
./build/pong
