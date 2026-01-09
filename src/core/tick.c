#include "tick.h"

#include "global.h"
#include "macros.h"
#include "move.h"

void tick(f32 dt) {
  if (move_ball(&Entities.ball, can_colide_with_ball, BALL_SPEED + s_acc,
                &ball_move_x, &ball_move_y, dt))
    s_acc += 6;

  if (Entities.enemy.y > Entities.ball.y - 5)
    move_rect(&Entities.enemy, can_colide_with_paddle, PADDLE_SPEED, UP, dt);
  else if (Entities.enemy.y < Entities.ball.y + 5)
    move_rect(&Entities.enemy, can_colide_with_paddle, PADDLE_SPEED, DOWN,
              dt);
}