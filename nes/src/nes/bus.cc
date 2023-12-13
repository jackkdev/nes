#include "bus.h"

namespace nes {

Bus::Bus() {}

Bus::~Bus() {}

std::shared_ptr<nes::Cpu> Bus::Cpu() { return cpu_; }

std::shared_ptr<std::array<u8, 2048>> Bus::CpuRam() { return cpu_ram_; }

} // namespace nes