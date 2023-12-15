//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#ifndef NES_NES_SRC_NES_GRAPHICS_RENDERER_H_
#define NES_NES_SRC_NES_GRAPHICS_RENDERER_H_

#include "window.h"

#include <vector>
#include <memory>

namespace nes {

class Layer;

class Renderer {
public:
  explicit Renderer(std::shared_ptr<Window> &window);
  ~Renderer();

  void PushLayer(std::unique_ptr<Layer> layer);

  void Draw();

private:
  std::shared_ptr<Window> window_;
  std::vector<std::unique_ptr<Layer>> layers_;
};

class Layer {
public:
  virtual ~Layer() = default;

  virtual const char *Name() = 0;

  virtual void OnDraw(const Renderer &renderer) = 0;
};

} // namespace nes

#endif // NES_NES_SRC_NES_GRAPHICS_RENDERER_H_
