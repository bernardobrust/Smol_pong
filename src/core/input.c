
#include "input.h"

#include <SDL3/SDL.h>

#include "global.h"
#include "macros.h"
#include "move.h"

void handle_input(f32 dt) {
  if (paused) return;

  const _Bool* keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_W])
    move_rect(&Entities.player, can_colide_with_paddle, PADDLE_SPEED, UP, dt);
  if (keyboard_state[SDL_SCANCODE_S])
    move_rect(&Entities.player, can_colide_with_paddle, PADDLE_SPEED, DOWN, dt);

  // ? Beacuse pause is not a continuous press, we'll handle it there
}
