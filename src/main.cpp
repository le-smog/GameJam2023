#include "InputHandler.hpp"
#include "LevelFactory.hpp"
#include "ObstaclesDrawer.hpp"
#include "PlayerDrawer.hpp"

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include <array>
#include <memory>

void draw_pause_icon(SDL_Renderer *renderer);

int main(int, char **) {

  LevelFactory level_factory = LevelFactory("levels");

  Level test = level_factory.make_level("level1");

  static constexpr Uint32 INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER;
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

  SDL_RenderSetLogicalSize(renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT);

  ObstaclesDrawer obstacle_drawer = ObstaclesDrawer(renderer);
  PlayerDrawer player_drawer = PlayerDrawer(renderer);

  auto &obstacles = test.getObstacles();
  Player &player = test.getPlayer();

  Uint64 start_time = SDL_GetTicks64();
  InputHandler input_handler;
  while (input_handler.should_continue()) {
    std::vector<Command> commands = input_handler.poll_commands();

    if (!input_handler.should_pause()) {
      Uint64 elapsed = SDL_GetTicks64() - start_time;
      player.update(obstacles, commands, elapsed);
    }
    start_time = SDL_GetTicks64();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if (input_handler.should_pause()) {
      draw_pause_icon(renderer);
    }
    obstacle_drawer.drawObstacle(obstacles);
    player_drawer.drawPlayer(player);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

void draw_pause_icon(SDL_Renderer *renderer) {
  std::array pause_rects{SDL_Rect{20, 20, 20, 80}, SDL_Rect{50, 20, 20, 80}};
  SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRects(renderer, pause_rects.data(), static_cast<int>(pause_rects.size()));
}
