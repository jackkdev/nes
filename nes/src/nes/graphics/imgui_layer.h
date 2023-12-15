//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#ifndef NES_NES_SRC_NES_GRAPHICS_IMGUI_LAYER_H_
#define NES_NES_SRC_NES_GRAPHICS_IMGUI_LAYER_H_

#include "renderer.h"
#include "nes/emulator/emulator.h"

#include <GLFW/glfw3.h>

namespace nes {

class ImGuiLayer: public Layer {
public:
  explicit ImGuiLayer(GLFWwindow *glfw_window,
                      std::shared_ptr<Emulator> emulator);
  ~ImGuiLayer() override;

  const char *Name() override;

  void OnDraw(const Renderer &renderer) override;

private:
  void DrawRegisters();
  void DrawMemoryMap();

private:
  GLFWwindow *glfw_window_;
  std::shared_ptr<Emulator> emulator_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_GRAPHICS_IMGUI_LAYER_H_
