#include "move.h"

#include <SDL3/SDL.h>
#include <stdbool.h>

#include "aabb.h"
#include "macros.h"

/*
    e = element to move
    cs = list of entities it could colide with
    sza = size of cs
    speed = e's speed
    dir = it's up or down
    dt = delta time
*/
void move_rect(SDL_FRect* e, const SDL_FRect* cs[], u32 sza, f32 speed,
               const enum Direction dir, f32 dt) {
  f32 delta = speed * dt;
  e->y += dir == UP ? -delta : delta;

  for (u32 i = 0; i < sza; ++i) {
    const SDL_FRect* c = cs[i];
    if (check_colision_rects(e, c)) {
      if (dir == UP) {
        e->y = c->y + c->h;
      } else {
        e->y = c->y - e->h;
      }
    }
  }
}