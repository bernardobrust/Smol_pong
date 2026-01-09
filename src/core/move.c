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
*/
void move_rect(SDL_FRect* e, const SDL_FRect* cs[], u32 sza, const u32 speed,
               const enum Direction dir) {
  i32 delta = speed;
  bool coliding;

  for (u32 i = 0; i < sza; ++i) {
    const SDL_FRect* c = cs[i];
    coliding = check_colision_rects(e, c);
    // Becomes 0 under any colision
    delta *= !coliding;
  }

  e->y += dir == UP ? -delta : delta;
  // Fallback
  if (delta == 0 && dir == UP)
    e->y += speed;
  else if (delta == 0)
    e->y -= speed;
}