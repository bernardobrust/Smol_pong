#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "macros.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

/* Initialization */
SDL_AppResult SDL_AppInit(void** appstate, i32 argc, char* argv[]) {
  SDL_SetAppMetadata(APP_NAME, "0.1", "com.be.pong");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer(APP_NAME, WIDTH, HEIGHT,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_SetRenderLogicalPresentation(renderer, 640, 480,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return SDL_APP_CONTINUE;
}

/* General input handling */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  // Closing the app
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

/* Tick */
SDL_AppResult SDL_AppIterate(void* appstate) {
    // We don't have circles natively in SDL3, so we run the rectangular ball
  SDL_FRect player, enemy, ball;
  player.x = 10, player.y = 10, player.w = 20, player.h = 100;
  enemy.x = 500, enemy.y = 30, enemy.w = 20, enemy.h = 100;
  ball.x = 300, ball.y = 30, ball.w = 10, ball.h = 10;

  // Black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

  // Clean then draw
  SDL_RenderClear(renderer);

  // White rects
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &player);
  SDL_RenderFillRect(renderer, &enemy);
  SDL_RenderFillRect(renderer, &ball);

  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

/* Termination (time to dealocate memory, save, etc.) */
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}