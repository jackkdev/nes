#include "renderer.h"

#include <glad/gl.h>

namespace nes {

Renderer::Renderer(const RendererOptions &options) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(i32(options.width), i32(options.height),
                             options.title.c_str(), nullptr, nullptr);

  glfwMakeContextCurrent(window_);
  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to load OpenGL.");
}

Renderer::~Renderer() {
  if (window_)
    glfwDestroyWindow(window_);

  glfwTerminate();
}

bool Renderer::ShouldClose() { return glfwWindowShouldClose(window_); }

void Renderer::EnqueueClose() {
  glfwSetWindowShouldClose(window_, true);
}

void Renderer::Present() {
  glfwPollEvents();
  glfwSwapBuffers(window_);
}

} // namespace nes