#ifndef NES_NES_SRC_NES_BUS_H_
#define NES_NES_SRC_NES_BUS_H_

#include "cpu.h"

namespace nes {

class Bus {
public:
  Bus();
  ~Bus();

  [[nodiscard]] std::shared_ptr<nes::Cpu> Cpu();
  [[nodiscard]] std::shared_ptr<std::array<u8, 2048>> CpuRam();

private:
  std::shared_ptr<nes::Cpu> cpu_;
  std::shared_ptr<std::array<u8, 2048>> cpu_ram_;
};

} // namespace nes

#endif // NES_NES_SRC_NES_BUS_H_
