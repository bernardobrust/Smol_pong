#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>

#include "global.h"
#include "input.h"
#include "macros.h"
#include "render.h"
#include "tick.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
u64 perf_freq;
u64 last_time = 0;
f32 dt = 0.0f;

const i32 middle = (i32)(HEIGHT / 2);

// ! Global shared mutable state
struct G_Entities Entities = {{10, middle - 50, 20, 100},
                              {WIDTH - 30, middle - 50, 20, 100},
                              {300, middle - 5, 10, 10},
                              {0, 0, WIDTH, 10},
                              {0, HEIGHT - 10, WIDTH, 10},
                            {0, 0, 0, HEIGHT},
                          {WIDTH, 0, 0, HEIGHT}};

const SDL_FRect* can_colide_with_paddle[] = {&Entities.barrier_up,
                                             &Entities.barrier_down};
const SDL_FRect* can_colide_with_ball[] = {&Entities.barrier_up,
                                           &Entities.barrier_down,
                                           &Entities.player, &Entities.enemy};
const SDL_FRect* entity_iterator = &Entities.player;

enum Direction ball_move_x = LEFT;
enum Direction ball_move_y = UP;
f32 s_acc = 0;

f32 p_score = 0, e_score = 0;

bool paused = true;

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
  SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  perf_freq = SDL_GetPerformanceFrequency();
  last_time = SDL_GetPerformanceCounter();

  return SDL_APP_CONTINUE;
}

/* Event handling */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) return SDL_APP_SUCCESS;

  // ? We'll handle pause here (discrete)
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE) paused = !paused;

  return SDL_APP_CONTINUE;
}

/* Tick */
SDL_AppResult SDL_AppIterate(void* appstate) {
  u64 current_time = SDL_GetPerformanceCounter();
  dt = (f32)((current_time - last_time) / (f32)perf_freq);
  last_time = current_time;

  handle_input(dt);
  tick(dt);  // Continuous logic
  render();

  return SDL_APP_CONTINUE;
}

/* Termination (time to dealocate memory, save, etc.) */
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}