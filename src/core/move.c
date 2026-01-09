#include "move.h"

#include <SDL3/SDL.h>
#include <assert.h>
#include <stdbool.h>

#include "aabb.h"
#include "macros.h"

/*
    e = element to move (paddle)
    cs = list of entities it could colide with
    speed = e's speed
    dir = up or down
    dt = delta time
*/
void move_rect(SDL_FRect* e, const SDL_FRect* cs[] /* 2 */, f32 speed,
               const enum Direction dir, f32 dt) {
  assert(dir == UP || dir == DOWN);

  f32 delta = speed * dt;
  e->y += dir == UP ? -delta : delta;

  for (u32 i = 0; i < 2; ++i) {
    const SDL_FRect* c = cs[i];
    if (check_colision_rects(e, c)) {
      if (dir == UP)
        e->y = c->y + c->h;
      else
        e->y = c->y - e->h;
    }
  }
}

/*
    e = element to move (ball)
    cs = list of entities it could colide with
    speed = e's speed
    dir_x = left or right (mutates)
    dir_y = up or down (mutates)
    dt = delta time

    returns if a colision happened
*/
bool move_ball(SDL_FRect* e, const SDL_FRect* cs[] /* 4 */, f32 speed,
               enum Direction* dir_x, enum Direction* dir_y, f32 dt) {
  assert(*dir_y == UP || *dir_y == DOWN);
  assert(*dir_x == LEFT || *dir_x == RIGHT);

  f32 delta = speed * dt;

  e->x += *dir_x == LEFT ? -delta : delta;
  e->y += *dir_y == UP ? -delta : delta;

  for (u32 i = 0; i < 4; ++i) {
    const SDL_FRect* c = cs[i];
    if (check_colision_rects(e, c)) {
      if (c->w > c->h) {
        if (*dir_y == UP) {
          e->y = c->y + c->h;
          *dir_y = DOWN;
        } else {
          e->y = c->y - e->h;
          *dir_y = UP;
        }
      } else {
        if (*dir_x == LEFT) {
          e->x = c->x + c->w;
          *dir_x = RIGHT;
        } else {
          e->x = c->x - e->w;
          *dir_x = LEFT;
        }
      }

      return true;
    }
  }

  return false;
}