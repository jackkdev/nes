#ifndef NES_NES_SRC_NES_H_
#define NES_NES_SRC_NES_H_

#include "cpu.h"

namespace nes {

class Emulator {
public:
  Emulator();
  ~Emulator();

  void Frame();

  [[nodiscard]] const std::shared_ptr<Cpu> &GetCpu() const;
  [[nodiscard]] const std::shared_ptr<CpuRam> &GetCpuRam() const;

private:
  std::shared_ptr<Cpu> cpu_;
  std::shared_ptr<CpuRam> cpu_ram_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_H_
