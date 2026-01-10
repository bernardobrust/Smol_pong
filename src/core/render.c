#include "render.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "global.h"

void render() {
  // Black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

  // Clean then draw
  SDL_RenderClear(renderer);

  // Score
  // ? Displayed as rectangles beacuse text is bloat
  SDL_SetRenderDrawColor(renderer, 0, 0, 150, 100);
  SDL_RenderFillRect(renderer, &entity_iterator[5]);
  SDL_RenderFillRect(renderer, &entity_iterator[6]);

  // White rects
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (u8 i = 0; i <= 4; ++i) SDL_RenderFillRect(renderer, &entity_iterator[i]);

  SDL_RenderPresent(renderer);
}