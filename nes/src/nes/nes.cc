#include "nes.h"

namespace nes {

Nes::Nes()
    : renderer_(std::make_shared<Renderer>(RendererOptions{
          .title = "nes v0.0.1",
          .width = 800,
          .height = 600,
      })),
      cpu_(std::make_shared<Cpu>()), cpu_ram_(std::make_shared<CpuRam>()) {
  cpu_->Attach(std::make_unique<CpuAddressSpace>(cpu_ram_));
}

Nes::~Nes() = default;

void Nes::Run() {
  while (!renderer_->ShouldClose()) {
    renderer_->Present();
  }
}

} // namespace nes