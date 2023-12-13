#include "cpu.h"

namespace nes {

Cpu::Cpu() : r_({.a = 0, .x = 0, .y = 0, .pc = 0, .s = 0, .p = 0}), as_() {}

Cpu::~Cpu() = default;

u8 Cpu::Clock() {
  return 0;
}

u8 Cpu::Read(u16 address) {
  return 0;
}

void Cpu::Write(u16 address, u8 value) {}

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