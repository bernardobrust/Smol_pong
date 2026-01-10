#include "tick.h"

#include "global.h"
#include "macros.h"
#include "move.h"

void tick(f32 dt) {
  if (move_ball(&Entities.ball, can_colide_with_ball, BALL_SPEED + s_acc,
                &ball_move_x, &ball_move_y, dt))
    s_acc += 6;

  const i32 offset = Entities.enemy.h / 2;
  if (Entities.enemy.y + offset > Entities.ball.y)
    move_rect(&Entities.enemy, can_colide_with_paddle, PADDLE_SPEED, UP, dt);
  else if (Entities.enemy.y - offset < Entities.ball.y)
    move_rect(&Entities.enemy, can_colide_with_paddle, PADDLE_SPEED, DOWN, dt);

  if (Entities.ball.x <= 0 || Entities.ball.x >= WIDTH) {
    if (Entities.ball.x <= 0) {
      // Enemy score
      e_score += 1;
      Entities.score_display_e.w -= 100;
    } else {
      // Player score
      p_score += 1;
      Entities.score_display_p.w += 100;
    }

    // This sucks, but it works for now
    if (p_score > MATCH_POINT || e_score > MATCH_POINT) {
      e_score = 0;
      Entities.score_display_e.w = 0;
      p_score = 0;
      Entities.score_display_p.w = 0;
    }

    // Resetting the ball
    Entities.ball.x = 300;
    Entities.ball.y = middle - 5;
    s_acc = 0;
  }
}