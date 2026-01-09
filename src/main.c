#include <SDL3/SDL_rect.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "macros.h"
#include "move.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

// ! Global shared mutable state
static struct Entities {
  SDL_FRect player, enemy, ball, barrier_up, barrier_down;
} Entities = {{10, 20, 20, 100},
              {500, 30, 20, 100},
              {300, 30, 10, 10},
              {0, 0, WIDTH, 10},
              {0, HEIGHT - 10, WIDTH, 10}};

static const SDL_FRect* can_colide_with_paddle[] = {&Entities.barrier_up,
                                              &Entities.barrier_down};
static const SDL_FRect *entity_iterator = &Entities.player;

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
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  if (event->type == SDL_EVENT_KEY_DOWN) {
    SDL_Scancode key = event->key.scancode;

    if (key == SDL_SCANCODE_W)
      move_rect(
          &Entities.player, can_colide_with_paddle,
          sizeof(can_colide_with_paddle) / sizeof(can_colide_with_paddle[0]),
          PADDLE_SPEED, UP);

    if (key == SDL_SCANCODE_S)
      move_rect(
          &Entities.player, can_colide_with_paddle,
          sizeof(can_colide_with_paddle) / sizeof(can_colide_with_paddle[0]),
          PADDLE_SPEED, DOWN);
  }

  return SDL_APP_CONTINUE;
}

/* Tick */
SDL_AppResult SDL_AppIterate(void* appstate) {
  // Black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

  // Clean then draw
  SDL_RenderClear(renderer);

  // White rects
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (u32 i = 0; i < sizeof(Entities)/sizeof(SDL_FRect); ++i) {
    SDL_RenderFillRect(renderer, &entity_iterator[i]);
  }

  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

/* Termination (time to dealocate memory, save, etc.) */
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}