#include "render.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "global.h"

void render() {
  // Black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

  // Clean then draw
  SDL_RenderClear(renderer);

  // White rects
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  // ? It's still a calculated value, not hardcoded because we still have the
  // ? score to implement
  for (u8 i = 0; i < sizeof(Entities) / sizeof(SDL_FRect); ++i)
    SDL_RenderFillRect(renderer, &entity_iterator[i]);

  SDL_RenderPresent(renderer);
}