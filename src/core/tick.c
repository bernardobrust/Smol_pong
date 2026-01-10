#include "tick.h"

#include "global.h"
#include "macros.h"
#include "move.h"

void tick(f32 dt) {
  // Do not tick when paused
  if (paused) return;

  // Localization
  SDL_FRect *ball = &Entities.ball;
  SDL_FRect *enemy = &Entities.enemy;
  SDL_FRect *display_e = &Entities.score_display_e;
  SDL_FRect *display_p = &Entities.score_display_p;

  // Ball movement
  if (move_ball(ball, can_colide_with_ball, BALL_SPEED + s_acc,
                &ball_move_x, &ball_move_y, dt))
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