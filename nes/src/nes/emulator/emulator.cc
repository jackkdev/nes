#include "emulator.h"

namespace nes {

Emulator::Emulator()
    : cpu_(std::make_shared<Cpu>()), cpu_ram_(std::make_shared<CpuRam>()) {
  cpu_->Attach(std::make_unique<CpuAddressSpace>(cpu_ram_));
}

Emulator::~Emulator() = default;

void Emulator::Frame() {
}

const std::shared_ptr<Cpu> &Emulator::GetCpu() const { return cpu_; }

const std::shared_ptr<CpuRam> &Emulator::GetCpuRam() const { return cpu_ram_; }

} // namespace nes