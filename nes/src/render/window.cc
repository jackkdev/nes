//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "window.h"

namespace nes {

u32 Window::s_window_count = 0;

Window::Window(const Window::Options &options) {
  if (s_window_count++ == 0)
    glfwInit();

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Pass the options as the data initializer.
  data_ = options;

  // Create the window handle.
  handle_ = glfwCreateWindow(
      options.width,
      options.height,
      options.title,
      nullptr,
      nullptr
  );

  // Setup the GLFW window context.
  glfwMakeContextCurrent(handle_);

  // Disable v-sync.
  glfwSwapInterval(0);

  // Setup the OpenGL context.
  if (!gladLoadGL(glfwGetProcAddress))
    exit(1);
}

Window::~Window() {
  if (--s_window_count == 0)
    glfwTerminate();
}

void Window::PollEvents() {
  glfwPollEvents();
}

void Window::SwapBuffers() const {
  glfwSwapBuffers(handle_);
}

const char *Window::GetTitle() const {
  return data_.title;
}

void Window::SetTitle(const char *title) {
  data_.title = title;
  glfwSetWindowTitle(handle_, title);
}

std::tuple<u32, u32> Window::GetSize() const {
  return std::make_tuple(data_.width, data_.height);
}

void Window::SetSize(i32 width, i32 height) {
  glfwSetWindowSize(handle_, width, height);
}

bool Window::ShouldClose() const {
  return glfwWindowShouldClose(handle_);
}

void Window::SetShouldClose(bool should_close) {
  glfwSetWindowShouldClose(handle_, should_close);
}

GLFWwindow *Window::GetHandle() {
  return handle_;
}

}