#pragma once

#include <SDL3/SDL.h>
#include <stdbool.h>

// We implement it inline since it's so simple
bool check_colision_rects(const SDL_FRect* a, const SDL_FRect* b) {
  return a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h &&
         a->y + a->h > b->y;
}