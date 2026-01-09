#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "macros.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern u64 perf_freq;
extern u64 last_time;
extern f32 dt;

// ! Global mutable state
struct G_Entities {
  SDL_FRect player, enemy, ball, barrier_up, barrier_down;
};
extern struct G_Entities Entities;

extern const SDL_FRect* can_colide_with_paddle[];
extern const SDL_FRect* entity_iterator;
