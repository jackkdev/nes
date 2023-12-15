//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#include "nes.h"

#include "graphics/imgui_layer.h"

namespace nes {

Nes::Nes()
    : emulator_(std::make_shared<Emulator>()),
      window_(std::make_shared<Window>(WindowOptions{
          .title = "NES Emulator - v0.1.0", .width = 800, .height = 600})),
      renderer_(std::make_shared<Renderer>(window_)) {
  renderer_->PushLayer(std::make_unique<ImGuiLayer>(window_->Handle(), emulator_));
}

Nes::~Nes() = default;

void Nes::Run() {
  while (!window_->ShouldClose()) {
    window_->PollEvents();

    if (window_->KeyPressed(nes::Key::kQ))
      window_->SetShouldClose(true);

    renderer_->Draw();

    window_->SwapBuffers();
  }
}

} // namespace nes