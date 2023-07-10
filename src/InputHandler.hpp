#pragma once

#include "Command.hpp"

#include <SDL2/SDL.h>

#include <vector>

class InputHandler {
private:
  bool keep_running{true};
  bool is_paused{false};
  SDL_GameController *controller{nullptr};

public:
  InputHandler() = default;
  ~InputHandler();

  std::vector<Command> poll_commands();
  bool should_continue() const;
  bool should_pause() const;
};
