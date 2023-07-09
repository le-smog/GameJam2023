#pragma once

#include "Command.hpp"

#include <SDL2/SDL.h>

#include <vector>

class InputHandler {
private:
  bool keep_running{true};

public:
  InputHandler() = default;

  std::vector<Command> poll_commands();
  bool should_continue() const;
};
