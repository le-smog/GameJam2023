#include "InputHandler.hpp"

#include <array>

static Command scancode_to_command(SDL_Scancode scancode) {
  switch (scancode) {
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
  case SDL_SCANCODE_SPACE:
    return Command::CMD_JUMP;
  case SDL_SCANCODE_Q:
  case SDL_SCANCODE_LEFT:
    return Command::CMD_LEFT;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    return Command::CMD_RIGHT;
  }
  return Command::CMD_NONE;
}

static std::vector<Command> get_commands_from_keystates() {
  constexpr std::array keys_to_check{SDL_SCANCODE_W,    SDL_SCANCODE_A,     SDL_SCANCODE_D,    SDL_SCANCODE_UP,
                                     SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_SPACE};
  std::vector<Command> commands;
  const Uint8 *key_states = SDL_GetKeyboardState(nullptr);
  for (SDL_Scancode code : keys_to_check) {
    if (key_states[code]) {
      Command cmd = scancode_to_command(code);
      commands.push_back(cmd);
    }
  }
  return commands;
}

std::vector<Command> InputHandler::poll_commands() {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_QUIT:
      keep_running = false;
      break;
    }
  }
  std::vector<Command> commands = get_commands_from_keystates();
  return commands;
}

bool InputHandler::should_continue() const { return keep_running; }
