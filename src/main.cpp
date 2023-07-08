#include <memory>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

int main(int, char **) {
  static constexpr Uint32 INIT_FLAGS = SDL_INIT_VIDEO;
  if (SDL_Init(INIT_FLAGS) < 0) {
    spdlog::error("Unable to init SDL: {}", SDL_GetError());
    return 1;
  }

  static constexpr int DEFAULT_WIDTH = 1280;
  static constexpr int DEFAULT_HEIGHT = 720;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (SDL_CreateWindowAndRenderer(DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer) < 0) {
    spdlog::error("Unable to create window and renderer: {}", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  bool should_continue = true;
  while (should_continue) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        should_continue = false;
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    static constexpr SDL_Rect rect{30, 40, 200, 300};
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}