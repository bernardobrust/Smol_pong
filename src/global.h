#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "macros.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern u64 perf_freq;
extern u64 last_time;
extern f32 dt;

extern const u8 middle;

// ! Global mutable state, handle with care
struct G_Entities {
  SDL_FRect player, enemy, ball, barrier_up, barrier_down, score_display_p,
      score_display_e;
};
extern struct G_Entities Entities;

extern const SDL_FRect* can_colide_with_paddle[];
extern const SDL_FRect* can_colide_with_ball[];

// ? We can iterate the entity struct like an array with this
extern const SDL_FRect* entity_iterator;

enum Direction { UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1 };

extern enum Direction ball_move_x, ball_move_y;
extern u8 s_acc, p_score, e_score;
extern bool paused;
