#ifndef NES_NES_SRC_NES_RENDERER_H_
#define NES_NES_SRC_NES_RENDERER_H_

#include "types.h"

#include <GLFW/glfw3.h>

namespace nes {

struct RendererOptions {
  std::string title;
  u32 width, height;
};

class Renderer {
public:
  explicit Renderer(const RendererOptions &options);
  ~Renderer();

  bool ShouldClose();
  void EnqueueClose();

  void Present();

private:
  GLFWwindow *window_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_RENDERER_H_
