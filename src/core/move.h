#pragma once

#include <SDL3/SDL.h>

#include "macros.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

// ? We can hardcode values in this case because we are sure that's what they will always be

// ? sza defaulted to 2 
void move_rect(SDL_FRect* e, const SDL_FRect* cs[] /* 2 */, f32 speed,
               const enum Direction dir, f32 dt);

// ? sza defaulted to 4
bool move_ball(SDL_FRect* e, const SDL_FRect* cs[] /* 4 */, f32 speed,
               enum Direction* dir_x, enum Direction* dir_y, f32 dt);