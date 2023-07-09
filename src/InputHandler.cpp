#include "InputHandler.hpp"

static Command keysym_to_command(SDL_Keysym keysym) {
  switch (keysym.scancode) {
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

std::vector<Command> InputHandler::poll_commands() {
  SDL_Event ev;
  std::vector<Command> commands;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_QUIT:
      keep_running = false;
      break;
    case SDL_KEYDOWN:
      Command cmd = keysym_to_command(ev.key.keysym);
      commands.push_back(cmd);
      break;
    }
  }
  return commands;
}

bool InputHandler::should_continue() const { return keep_running; }
