#include "InputHandler.hpp"

#include <spdlog/spdlog.h>

#include <array>

static SDL_GameController *try_open_controller(Sint32 controller_id);
static Command scancode_to_command(SDL_Scancode scancode);
static Command controller_button_to_command(SDL_GameControllerButton button);

/* Appends all the commands from the keyboard into the command_buffer */
static void get_commands_from_keystates(std::vector<Command> &command_buffer);

/* Appends all the commands from the controller into the command_buffer */
static void get_commands_from_controller(std::vector<Command> &command_buffer, SDL_GameController *controller);

InputHandler::~InputHandler() {
  if (controller) {
    SDL_GameControllerClose(controller);
  }
}

std::vector<Command> InputHandler::poll_commands() {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_QUIT:
      keep_running = false;
      break;
    case SDL_CONTROLLERDEVICEADDED:
      if (!SDL_GameControllerGetAttached(controller)) {
        controller = try_open_controller(ev.cdevice.which);
      }
      break;
    case SDL_CONTROLLERDEVICEREMOVED:
      spdlog::warn("Controller disconnected");
      break;
    case SDL_KEYDOWN:
      if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE && !ev.key.repeat) {
        is_paused = !is_paused;
      }
      break;
    case SDL_CONTROLLERBUTTONDOWN:
      if (ev.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
        is_paused = !is_paused;
      }
      break;
    }
  }
  std::vector<Command> commands;
  get_commands_from_keystates(commands);
  get_commands_from_controller(commands, controller);
  return commands;
}

bool InputHandler::should_continue() const { return keep_running; }

bool InputHandler::should_pause() const { return is_paused; }

static SDL_GameController *try_open_controller(Sint32 controller_id) {
  SDL_GameController *result = SDL_GameControllerOpen(controller_id);
  if (result == nullptr) {
    spdlog::warn("Unable to open controller: {}", SDL_GetError());
  } else {
    spdlog::info("Controller '{}' connected", SDL_GameControllerNameForIndex(controller_id));
  }
  return result;
}

static Command scancode_to_command(SDL_Scancode scancode) {
  switch (scancode) {
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
  case SDL_SCANCODE_SPACE:
    return Command::CMD_JUMP;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    return Command::CMD_LEFT;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    return Command::CMD_RIGHT;
  }
  return Command::CMD_NONE;
}

static Command controller_button_to_command(SDL_GameControllerButton button) {
  switch (button) {
  case SDL_CONTROLLER_BUTTON_A:
  case SDL_CONTROLLER_BUTTON_B:
  case SDL_CONTROLLER_BUTTON_X:
  case SDL_CONTROLLER_BUTTON_Y:
  case SDL_CONTROLLER_BUTTON_DPAD_UP:
    return Command::CMD_JUMP;
  case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
    return Command::CMD_LEFT;
  case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
    return Command::CMD_RIGHT;
  }
  return Command::CMD_NONE;
}

static void get_commands_from_keystates(std::vector<Command> &command_buffer) {
  constexpr std::array keys_to_check{SDL_SCANCODE_W,    SDL_SCANCODE_A,     SDL_SCANCODE_D,    SDL_SCANCODE_UP,
                                     SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_SPACE};
  const Uint8 *key_states = SDL_GetKeyboardState(nullptr);
  for (SDL_Scancode code : keys_to_check) {
    if (key_states[code]) {
      Command cmd = scancode_to_command(code);
      command_buffer.push_back(cmd);
    }
  }
}

static void get_commands_from_controller(std::vector<Command> &command_buffer, SDL_GameController *controller) {
  constexpr std::array buttons_to_check{SDL_CONTROLLER_BUTTON_A,         SDL_CONTROLLER_BUTTON_B,
                                        SDL_CONTROLLER_BUTTON_X,         SDL_CONTROLLER_BUTTON_Y,
                                        SDL_CONTROLLER_BUTTON_DPAD_UP,   SDL_CONTROLLER_BUTTON_DPAD_LEFT,
                                        SDL_CONTROLLER_BUTTON_DPAD_RIGHT};
  for (SDL_GameControllerButton button : buttons_to_check) {
    if (SDL_GameControllerGetButton(controller, button) == SDL_PRESSED) {
      Command cmd = controller_button_to_command(button);
      command_buffer.push_back(cmd);
    }
  }
}
