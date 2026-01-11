# Pong, but smol

This is a tiny implementation of the classic game Pong. Like, less than 6.2 kilobytes.

Some things may be wrong here, maybe I missed some optimizations, IDK, don't take this repo too seriously.

## How tiny?

We're talking a few kilobytes. The binary is small because we're doing some pretty extreme things to get the size down:

- We're not linking against the C standard library (`-nostdlib`).
- We're using link-time optimization (LTO).
- We're stripping the binary.
- We're using a bunch of compiler flags to squeeze out every last byte.

The main dependency is SDL3, which we're linking statically.

## How to build and run

You'll need Meson and a C compiler.

```bash
meson setup build
meson compile -C build
./build/pong
```

## Why?

Because it's fun to see how small you can make things. This is an exercise in minimalism.

## We're not masochists

Could we make it even smaller? Sure. We could ditch SDL3 and write all the platform-specific code to open a window, handle input, and draw pixels ourselves by rawdogging kernel syscalls. But we're not masochists. This is a fun side project, not a torture session. We're trying to have a good time here.
