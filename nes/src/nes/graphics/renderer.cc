//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#include "renderer.h"

#include <glad/gl.h>

namespace nes {

Renderer::Renderer(std::shared_ptr<Window> &window) : window_(window) {
}

Renderer::~Renderer() = default;

void Renderer::PushLayer(std::unique_ptr<Layer> layer) {
  layers_.push_back(std::move(layer));
}

void Renderer::Draw() {
  i32 display_w, display_h;
  window_->GetFramebufferSize(display_w, display_h);
  glViewport(0, 0, display_w, display_h);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for (const auto &layer : layers_)
    layer->OnDraw(*this);
}

} // namespace nes