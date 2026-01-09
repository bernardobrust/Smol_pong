#pragma once

#include <SDL3/SDL.h>

#include "macros.h"

enum Direction { UP, DOWN };

void move_rect(SDL_FRect* e, const SDL_FRect* cs[], u32 sza, f32 speed,
               const enum Direction dir, f32 dt);
