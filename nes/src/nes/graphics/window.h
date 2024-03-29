//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#ifndef NES_NES_SRC_NES_GRAPHICS_WINDOW_H_
#define NES_NES_SRC_NES_GRAPHICS_WINDOW_H_

#include "nes/types.h"

#include <GLFW/glfw3.h>
#include <string>

namespace nes {

enum class Key;

struct WindowOptions {
  std::string title;
  u32 width, height;
};

class Window {
public:
  explicit Window(const WindowOptions &options);
  ~Window();

  void SwapBuffers() const;
  void PollEvents() const;

  [[nodiscard]] bool KeyPressed(Key key) const;

  [[nodiscard]] bool ShouldClose() const;
  void SetShouldClose(bool should_close);

  void GetFramebufferSize(i32 &width, i32 &height);

  [[nodiscard]] GLFWwindow *Handle() const;

private:
  GLFWwindow *window_;
};

enum class Key: i32 {
  kSpace = GLFW_KEY_SPACE,
  kApostrophe = GLFW_KEY_APOSTROPHE,
  kComma = GLFW_KEY_COMMA,
  kMinus = GLFW_KEY_MINUS,
  kPeriod = GLFW_KEY_PERIOD,
  kSlash = GLFW_KEY_SLASH,
  k0 = GLFW_KEY_0,
  k1 = GLFW_KEY_1,
  k2 = GLFW_KEY_2,
  k3 = GLFW_KEY_3,
  k4 = GLFW_KEY_4,
  k5 = GLFW_KEY_5,
  k6 = GLFW_KEY_6,
  k7 = GLFW_KEY_7,
  k8 = GLFW_KEY_8,
  k9 = GLFW_KEY_9,
  kSemicolon = GLFW_KEY_SEMICOLON,
  kEqual = GLFW_KEY_EQUAL,
  kA = GLFW_KEY_A,
  kB = GLFW_KEY_B,
  kC = GLFW_KEY_C,
  kD = GLFW_KEY_D,
  kE = GLFW_KEY_E,
  kF = GLFW_KEY_F,
  kG = GLFW_KEY_G,
  kH = GLFW_KEY_H,
  kI = GLFW_KEY_I,
  kJ = GLFW_KEY_J,
  kK = GLFW_KEY_K,
  kL = GLFW_KEY_L,
  kM = GLFW_KEY_M,
  kN = GLFW_KEY_N,
  kO = GLFW_KEY_O,
  kP = GLFW_KEY_P,
  kQ = GLFW_KEY_Q,
  kR = GLFW_KEY_R,
  kS = GLFW_KEY_S,
  kT = GLFW_KEY_T,
  kU = GLFW_KEY_U,
  kV = GLFW_KEY_V,
  kW = GLFW_KEY_W,
  kX = GLFW_KEY_X,
  kY = GLFW_KEY_Y,
  kZ = GLFW_KEY_Z,
  kLeftBracket = GLFW_KEY_LEFT_BRACKET,
  kBackslash = GLFW_KEY_BACKSLASH,
  kRightBracket = GLFW_KEY_RIGHT_BRACKET,
  kGraveAccent = GLFW_KEY_GRAVE_ACCENT,
  kWorld1 = GLFW_KEY_WORLD_1,
  kWorld2 = GLFW_KEY_WORLD_2,
  kEscape = GLFW_KEY_ESCAPE,
  kEnter = GLFW_KEY_ENTER,
  kTab = GLFW_KEY_TAB,
  kBackspace = GLFW_KEY_BACKSPACE,
  kInsert = GLFW_KEY_INSERT,
  kDelete = GLFW_KEY_DELETE,
  kRight = GLFW_KEY_RIGHT,
  kLeft = GLFW_KEY_LEFT,
  kDown = GLFW_KEY_DOWN,
  kUp = GLFW_KEY_UP,
  kPageUp = GLFW_KEY_PAGE_UP,
  kPageDown = GLFW_KEY_PAGE_DOWN,
  kHome = GLFW_KEY_HOME,
  kEnd = GLFW_KEY_END,
  kCapsLock = GLFW_KEY_CAPS_LOCK,
  kScrollLock = GLFW_KEY_SCROLL_LOCK,
  kNumLock = GLFW_KEY_NUM_LOCK,
  kPrintScreen = GLFW_KEY_PRINT_SCREEN,
  kPause = GLFW_KEY_PAUSE,
  kF1 = GLFW_KEY_F1,
  kF2 = GLFW_KEY_F2,
  kF3 = GLFW_KEY_F3,
  kF4 = GLFW_KEY_F4,
  kF5 = GLFW_KEY_F5,
  kF6 = GLFW_KEY_F6,
  kF7 = GLFW_KEY_F7,
  kF8 = GLFW_KEY_F8,
  kF9 = GLFW_KEY_F9,
  kF10 = GLFW_KEY_F10,
  kF11 = GLFW_KEY_F11,
  kF12 = GLFW_KEY_F12,
  kF13 = GLFW_KEY_F13,
  kF14 = GLFW_KEY_F14,
  kF15 = GLFW_KEY_F15,
  kF16 = GLFW_KEY_F16,
  kF17 = GLFW_KEY_F17,
  kF18 = GLFW_KEY_F18,
  kF19 = GLFW_KEY_F19,
  kF20 = GLFW_KEY_F20,
  kF21 = GLFW_KEY_F21,
  kF22 = GLFW_KEY_F22,
  kF23 = GLFW_KEY_F23,
  kF24 = GLFW_KEY_F24,
  kF25 = GLFW_KEY_F25,
  kKp0 = GLFW_KEY_KP_0,
  kKp1 = GLFW_KEY_KP_1,
  kKp2 = GLFW_KEY_KP_2,
  kKp3 = GLFW_KEY_KP_3,
  kKp4 = GLFW_KEY_KP_4,
  kKp5 = GLFW_KEY_KP_5,
  kKp6 = GLFW_KEY_KP_6,
  kKp7 = GLFW_KEY_KP_7,
  kKp8 = GLFW_KEY_KP_8,
  kKp9 = GLFW_KEY_KP_9,
  kKpDecimal = GLFW_KEY_KP_DECIMAL,
  kKpDivide = GLFW_KEY_KP_DIVIDE,
  kKpMultiply = GLFW_KEY_KP_MULTIPLY,
  kKpSubtract = GLFW_KEY_KP_SUBTRACT,
  kKpAdd = GLFW_KEY_KP_ADD,
  kKpEnter = GLFW_KEY_KP_ENTER,
  kKpEqual = GLFW_KEY_KP_EQUAL,
  kLeftShift = GLFW_KEY_LEFT_SHIFT,
  kLeftControl = GLFW_KEY_LEFT_CONTROL,
  kLeftAlt = GLFW_KEY_LEFT_ALT,
  kLeftSuper = GLFW_KEY_LEFT_SUPER,
  kRightShift = GLFW_KEY_RIGHT_SHIFT,
  kRightControl = GLFW_KEY_RIGHT_CONTROL,
  kRightAlt = GLFW_KEY_RIGHT_ALT,
  kRightSuper = GLFW_KEY_RIGHT_SUPER,
  kMenu = GLFW_KEY_MENU,
};

} // namespace nes

#endif // NES_NES_SRC_NES_GRAPHICS_WINDOW_H_
