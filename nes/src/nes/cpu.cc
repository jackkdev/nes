#include "cpu.h"

namespace nes {

CpuAddressSpace::CpuAddressSpace(const std::shared_ptr<CpuRam> &ram)
    : ram_(ram) {}

CpuAddressSpace::~CpuAddressSpace() = default;

u8 CpuAddressSpace::Read(u16 address) { return 0; }

void CpuAddressSpace::Write(u16 address, u8 data) {}

Cpu::Cpu() : r_({.a = 0, .x = 0, .y = 0, .pc = 0, .s = 0, .p = 0}) {}

Cpu::~Cpu() = default;

void Cpu::Attach(std::unique_ptr<CpuAddressSpace> as) {
  as_ = std::move(as);
}

u8 Cpu::Clock() { return 0; }

/// <editor-fold desc="Addressing Modes">
u8 Cpu::IMP() { return 0; }

u8 Cpu::ACC() { return 0; }

u8 Cpu::IMM() { return 0; }

u8 Cpu::ZPG() { return 0; }

u8 Cpu::ABS() { return 0; }

u8 Cpu::REL() { return 0; }

u8 Cpu::IND() { return 0; }

u8 Cpu::ZPX() { return 0; }

u8 Cpu::ZPY() { return 0; }

u8 Cpu::ABX() { return 0; }

u8 Cpu::ABY() { return 0; }

u8 Cpu::IXI() { return 0; }

u8 Cpu::IIX() { return 0; }
/// </editor-fold>

} // namespace nes