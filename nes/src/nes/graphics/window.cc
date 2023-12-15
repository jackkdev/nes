//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#include "window.h"

#include <glad/gl.h>

namespace nes {

Window::Window(const WindowOptions &options) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW.");

  window_ = glfwCreateWindow(
      i32(options.width), i32(options.height), options.title.c_str(),
      nullptr, nullptr
      );

  glfwMakeContextCurrent(window_);
  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize OpenGL.");
}

Window::~Window() {
  if (window_)
    glfwDestroyWindow(window_);

  glfwTerminate();
}

void Window::SwapBuffers() const {
  glfwSwapBuffers(window_);
}

void Window::PollEvents() const {
  glfwPollEvents();
}

bool Window::KeyPressed(Key key) const { return glfwGetKey(window_, i32(key)) == GLFW_PRESS; }

bool Window::ShouldClose() const { return glfwWindowShouldClose(window_); }

void Window::SetShouldClose(bool should_close) {
  glfwSetWindowShouldClose(window_, should_close);
}

void Window::GetFramebufferSize(i32 &width, i32 &height) {
  i32 out_width, out_height;
  glfwGetFramebufferSize(window_, &out_width, &out_height);

  width = out_width;
  height = out_height;
}

GLFWwindow *Window::Handle() const { return window_; }

} // namespace nes