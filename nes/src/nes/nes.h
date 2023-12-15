//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#ifndef NES_NES_SRC_NES_NES_H_
#define NES_NES_SRC_NES_NES_H_

#include "emulator/emulator.h"
#include "graphics/window.h"
#include "graphics/renderer.h"

#include <memory>

namespace nes {

class Nes {
public:
  Nes();
  ~Nes();

  void Run();

private:
  std::shared_ptr<Emulator> emulator_;
  std::shared_ptr<Window> window_;
  std::shared_ptr<Renderer> renderer_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_NES_H_
