//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_WINDOW_H_
#define NES_NES_SRC_RENDER_WINDOW_H_

#include "../util/types.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/gl.h>

#include <tuple>

namespace nes {

// Provides a wrapper around the GLFW window system.
// The Window class emits events based on the GLFW window event that happened.
class Window {
 private:
  static u32 s_window_count;

 public:
  struct Data {
    const char *title;
    i32 width, height;
  };

  using Options = Data;

 public:
  explicit Window(const Options &options);
  ~Window();

  // Polls window events such as keyboard input, cursor input, etc.
  static void PollEvents();

  // Swaps the back buffers to display the current image.
  void SwapBuffers() const;

  [[nodiscard]] const char *GetTitle() const;
  void SetTitle(const char *title);

  [[nodiscard]] std::tuple<u32, u32> GetSize() const;
  void SetSize(i32 width, i32 height);

  [[nodiscard]] bool ShouldClose() const;
  void SetShouldClose(bool should_close);

  GLFWwindow *GetHandle();

 private:
  GLFWwindow *handle_ = nullptr;
  Data data_ = {};
};

}

#endif //NES_NES_SRC_RENDER_WINDOW_H_
