#include "tick.h"

#include "aabb.h"
#include "global.h"
#include "macros.h"

/*
    e = element to move (paddle)
    cs = list of entities it could colide with
    speed = e's speed
    dir = up or down
    dt = delta time
*/
static void move_rect(SDL_FRect* e, const SDL_FRect* cs[] /* 2 */, f32 speed,
                      const enum Direction dir, f32 dt) {
  e->y += (f32)dir * (speed * dt);

  for (u8 i = 0; i < 2; ++i) {
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
static bool move_ball(SDL_FRect* e, const SDL_FRect* cs[] /* 4 */, f32 speed,
                      enum Direction* dir_x, enum Direction* dir_y, f32 dt) {
  f32 delta = speed * dt;

  e->x += (f32)*dir_x * delta;
  e->y += (f32)*dir_y * delta;

  for (u8 i = 0; i < 4; ++i) {
    const SDL_FRect* c = cs[i];
    if (check_colision_rects(e, c)) {
      if (c->w > c->h) {
        if (*dir_y == UP)
          e->y = c->y + c->h;
        else
          e->y = c->y - e->h;

        *dir_y *= -1;
      } else {
        if (*dir_x == LEFT)
          e->x = c->x + c->w;
        else
          e->x = c->x - e->w;

        *dir_x *= -1;
      }

      return true;
    }
  }

  return false;
}

void handle_input(f32 dt) {
  if (paused) return;

  const _Bool* keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_W])
    move_rect(&Entities.player, can_colide_with_paddle, PADDLE_SPEED, UP, dt);
  if (keyboard_state[SDL_SCANCODE_S])
    move_rect(&Entities.player, can_colide_with_paddle, PADDLE_SPEED, DOWN, dt);
}

void tick(f32 dt) {
  // Do not tick when paused
  if (paused) return;

  // Localization
  SDL_FRect* ball = &Entities.ball;
  SDL_FRect* enemy = &Entities.enemy;
  SDL_FRect* display_e = &Entities.score_display_e;
  SDL_FRect* display_p = &Entities.score_display_p;

  // Ball movement
  if (move_ball(ball, can_colide_with_ball, BALL_SPEED + s_acc, &ball_move_x,
                &ball_move_y, dt))
    s_acc += BALL_SPEED_INCREASE;

  // Enemy movement
  const i32 offset = enemy->h / 2;
  if (enemy->y + offset > ball->y)
    move_rect(enemy, can_colide_with_paddle, PADDLE_SPEED, UP, dt);
  else if (enemy->y - offset < ball->y)
    move_rect(enemy, can_colide_with_paddle, PADDLE_SPEED, DOWN, dt);

  // Scoring
  if (ball->x <= 0 || ball->x >= WIDTH) {
    if (ball->x <= 0) {
      // Enemy score
      e_score += 1;
      display_e->w -= 100;
    } else {
      // Player score
      p_score += 1;
      display_p->w += 100;
    }

    if (p_score > MATCH_POINT || e_score > MATCH_POINT) {
      e_score = 0;
      display_e->w = 0;
      p_score = 0;
      display_p->w = 0;
    }

    // Resetting the ball
    ball->x = 300;
    ball->y = middle - 5;
    s_acc = 0;

    // Pausing
    paused = true;
  }
}