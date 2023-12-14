#ifndef NES_NES_SRC_NES_H_
#define NES_NES_SRC_NES_H_

#include "renderer.h"
#include "cpu.h"

namespace nes {

class Nes {
public:
  Nes();
  ~Nes();

  void Run();

private:
  std::shared_ptr<Renderer> renderer_;

  std::shared_ptr<Cpu> cpu_;
  std::shared_ptr<CpuRam> cpu_ram_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_H_
