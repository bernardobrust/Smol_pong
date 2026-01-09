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
}