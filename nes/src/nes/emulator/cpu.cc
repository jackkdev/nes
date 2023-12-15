#include "cpu.h"

namespace nes {

CpuAddressSpace::CpuAddressSpace(const std::shared_ptr<CpuRam> &ram)
    : ram_(ram) {}

CpuAddressSpace::~CpuAddressSpace() = default;

u8 CpuAddressSpace::Read(u16 address) {
  if (address <= 0x1FFF)
    return ram_->at(address % 0x800);

  return 0;
}

void CpuAddressSpace::Write(u16 address, u8 data) {
  if (address <= 0x1FFF) {
    (*ram_)[address % 0x800] = data;
    return;
  }
}

Cpu::Cpu()
    : as_(nullptr), r_({.a = 0, .x = 0, .y = 0, .pc = 0, .s = 0, .p = 0}),
      lookup_(256), cycles_(0), inst_(nullptr), arg_(0), arg_addr_(0) {
  using a = Cpu;

  lookup_ = {
      // clang-format off
        { "BRK", &a::BRK, &a::IMM, 7 }, { "ORA", &a::ORA, &a::IZX, 6 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 3 }, { "ORA", &a::ORA, &a::ZP0, 3 }, { "ASL", &a::ASL, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "PHP", &a::PHP, &a::IMP, 3 }, { "ORA", &a::ORA, &a::IMM, 2 }, { "ASL", &a::ASL, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::NOP, &a::IMP, 4 }, { "ORA", &a::ORA, &a::ABS, 4 }, { "ASL", &a::ASL, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BPL", &a::BPL, &a::REL, 2 }, { "ORA", &a::ORA, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "ORA", &a::ORA, &a::ZPX, 4 }, { "ASL", &a::ASL, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "CLC", &a::CLC, &a::IMP, 2 }, { "ORA", &a::ORA, &a::ABY, 4 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "ORA", &a::ORA, &a::ABX, 4 }, { "ASL", &a::ASL, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
        { "JSR", &a::JSR, &a::ABS, 6 }, { "AND", &a::AND, &a::IZX, 6 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "BIT", &a::BIT, &a::ZP0, 3 }, { "AND", &a::AND, &a::ZP0, 3 }, { "ROL", &a::ROL, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "PLP", &a::PLP, &a::IMP, 4 }, { "AND", &a::AND, &a::IMM, 2 }, { "ROL", &a::ROL, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "BIT", &a::BIT, &a::ABS, 4 }, { "AND", &a::AND, &a::ABS, 4 }, { "ROL", &a::ROL, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BMI", &a::BMI, &a::REL, 2 }, { "AND", &a::AND, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "AND", &a::AND, &a::ZPX, 4 }, { "ROL", &a::ROL, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "SEC", &a::SEC, &a::IMP, 2 }, { "AND", &a::AND, &a::ABY, 4 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "AND", &a::AND, &a::ABX, 4 }, { "ROL", &a::ROL, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
        { "RTI", &a::RTI, &a::IMP, 6 }, { "EOR", &a::EOR, &a::IZX, 6 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 3 }, { "EOR", &a::EOR, &a::ZP0, 3 }, { "LSR", &a::LSR, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "PHA", &a::PHA, &a::IMP, 3 }, { "EOR", &a::EOR, &a::IMM, 2 }, { "LSR", &a::LSR, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "JMP", &a::JMP, &a::ABS, 3 }, { "EOR", &a::EOR, &a::ABS, 4 }, { "LSR", &a::LSR, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BVC", &a::BVC, &a::REL, 2 }, { "EOR", &a::EOR, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "EOR", &a::EOR, &a::ZPX, 4 }, { "LSR", &a::LSR, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "CLI", &a::CLI, &a::IMP, 2 }, { "EOR", &a::EOR, &a::ABY, 4 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "EOR", &a::EOR, &a::ABX, 4 }, { "LSR", &a::LSR, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
        { "RTS", &a::RTS, &a::IMP, 6 }, { "ADC", &a::ADC, &a::IZX, 6 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 3 }, { "ADC", &a::ADC, &a::ZP0, 3 }, { "ROR", &a::ROR, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "PLA", &a::PLA, &a::IMP, 4 }, { "ADC", &a::ADC, &a::IMM, 2 }, { "ROR", &a::ROR, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "JMP", &a::JMP, &a::IND, 5 }, { "ADC", &a::ADC, &a::ABS, 4 }, { "ROR", &a::ROR, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BVS", &a::BVS, &a::REL, 2 }, { "ADC", &a::ADC, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "ADC", &a::ADC, &a::ZPX, 4 }, { "ROR", &a::ROR, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "SEI", &a::SEI, &a::IMP, 2 }, { "ADC", &a::ADC, &a::ABY, 4 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "ADC", &a::ADC, &a::ABX, 4 }, { "ROR", &a::ROR, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
        { "???", &a::NOP, &a::IMP, 2 }, { "STA", &a::STA, &a::IZX, 6 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 6 }, { "STY", &a::STY, &a::ZP0, 3 }, { "STA", &a::STA, &a::ZP0, 3 }, { "STX", &a::STX, &a::ZP0, 3 }, { "???", &a::XXX, &a::IMP, 3 }, { "DEY", &a::DEY, &a::IMP, 2 }, { "???", &a::NOP, &a::IMP, 2 }, { "TXA", &a::TXA, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "STY", &a::STY, &a::ABS, 4 }, { "STA", &a::STA, &a::ABS, 4 }, { "STX", &a::STX, &a::ABS, 4 }, { "???", &a::XXX, &a::IMP, 4 },
        { "BCC", &a::BCC, &a::REL, 2 }, { "STA", &a::STA, &a::IZY, 6 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 6 }, { "STY", &a::STY, &a::ZPX, 4 }, { "STA", &a::STA, &a::ZPX, 4 }, { "STX", &a::STX, &a::ZPY, 4 }, { "???", &a::XXX, &a::IMP, 4 }, { "TYA", &a::TYA, &a::IMP, 2 }, { "STA", &a::STA, &a::ABY, 5 }, { "TXS", &a::TXS, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 5 }, { "???", &a::NOP, &a::IMP, 5 }, { "STA", &a::STA, &a::ABX, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "???", &a::XXX, &a::IMP, 5 },
        { "LDY", &a::LDY, &a::IMM, 2 }, { "LDA", &a::LDA, &a::IZX, 6 }, { "LDX", &a::LDX, &a::IMM, 2 }, { "???", &a::XXX, &a::IMP, 6 }, { "LDY", &a::LDY, &a::ZP0, 3 }, { "LDA", &a::LDA, &a::ZP0, 3 }, { "LDX", &a::LDX, &a::ZP0, 3 }, { "???", &a::XXX, &a::IMP, 3 }, { "TAY", &a::TAY, &a::IMP, 2 }, { "LDA", &a::LDA, &a::IMM, 2 }, { "TAX", &a::TAX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "LDY", &a::LDY, &a::ABS, 4 }, { "LDA", &a::LDA, &a::ABS, 4 }, { "LDX", &a::LDX, &a::ABS, 4 }, { "???", &a::XXX, &a::IMP, 4 },
        { "BCS", &a::BCS, &a::REL, 2 }, { "LDA", &a::LDA, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 5 }, { "LDY", &a::LDY, &a::ZPX, 4 }, { "LDA", &a::LDA, &a::ZPX, 4 }, { "LDX", &a::LDX, &a::ZPY, 4 }, { "???", &a::XXX, &a::IMP, 4 }, { "CLV", &a::CLV, &a::IMP, 2 }, { "LDA", &a::LDA, &a::ABY, 4 }, { "TSX", &a::TSX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 4 }, { "LDY", &a::LDY, &a::ABX, 4 }, { "LDA", &a::LDA, &a::ABX, 4 }, { "LDX", &a::LDX, &a::ABY, 4 }, { "???", &a::XXX, &a::IMP, 4 },
        { "CPY", &a::CPY, &a::IMM, 2 }, { "CMP", &a::CMP, &a::IZX, 6 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "CPY", &a::CPY, &a::ZP0, 3 }, { "CMP", &a::CMP, &a::ZP0, 3 }, { "DEC", &a::DEC, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "INY", &a::INY, &a::IMP, 2 }, { "CMP", &a::CMP, &a::IMM, 2 }, { "DEX", &a::DEX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 2 }, { "CPY", &a::CPY, &a::ABS, 4 }, { "CMP", &a::CMP, &a::ABS, 4 }, { "DEC", &a::DEC, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BNE", &a::BNE, &a::REL, 2 }, { "CMP", &a::CMP, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "CMP", &a::CMP, &a::ZPX, 4 }, { "DEC", &a::DEC, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "CLD", &a::CLD, &a::IMP, 2 }, { "CMP", &a::CMP, &a::ABY, 4 }, { "NOP", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "CMP", &a::CMP, &a::ABX, 4 }, { "DEC", &a::DEC, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
        { "CPX", &a::CPX, &a::IMM, 2 }, { "SBC", &a::SBC, &a::IZX, 6 }, { "???", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "CPX", &a::CPX, &a::ZP0, 3 }, { "SBC", &a::SBC, &a::ZP0, 3 }, { "INC", &a::INC, &a::ZP0, 5 }, { "???", &a::XXX, &a::IMP, 5 }, { "INX", &a::INX, &a::IMP, 2 }, { "SBC", &a::SBC, &a::IMM, 2 }, { "NOP", &a::NOP, &a::IMP, 2 }, { "???", &a::SBC, &a::IMP, 2 }, { "CPX", &a::CPX, &a::ABS, 4 }, { "SBC", &a::SBC, &a::ABS, 4 }, { "INC", &a::INC, &a::ABS, 6 }, { "???", &a::XXX, &a::IMP, 6 },
        { "BEQ", &a::BEQ, &a::REL, 2 }, { "SBC", &a::SBC, &a::IZY, 5 }, { "???", &a::XXX, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 8 }, { "???", &a::NOP, &a::IMP, 4 }, { "SBC", &a::SBC, &a::ZPX, 4 }, { "INC", &a::INC, &a::ZPX, 6 }, { "???", &a::XXX, &a::IMP, 6 }, { "SED", &a::SED, &a::IMP, 2 }, { "SBC", &a::SBC, &a::ABY, 4 }, { "NOP", &a::NOP, &a::IMP, 2 }, { "???", &a::XXX, &a::IMP, 7 }, { "???", &a::NOP, &a::IMP, 4 }, { "SBC", &a::SBC, &a::ABX, 4 }, { "INC", &a::INC, &a::ABX, 7 }, { "???", &a::XXX, &a::IMP, 7 },
      // clang-format on
  };
}

Cpu::~Cpu() = default;

void Cpu::Attach(std::unique_ptr<CpuAddressSpace> as) { as_ = std::move(as); }

const CpuRegisters &Cpu::GetRegisters() const { return r_; }

u8 Cpu::Clock() {
  if (cycles_ == 0) {
    arg_ = 0;
    arg_addr_ = 0;

    auto start_pc = r_.pc;

    opcode_ = as_->Read(r_.pc++);
    inst_ = &lookup_[opcode_];

    cycles_ = inst_->cycles;

    auto extra_1 = (this->*lookup_[opcode_].addressing_mode_handler)();

    if (inst_->addressing_mode_handler != &Cpu::REL &&
        inst_->addressing_mode_handler != &Cpu::IMP)
      Fetch();

    auto extra_2 = (this->*lookup_[opcode_].operation_handler)();

    cycles_ += (extra_1 & extra_2);

    std::cout << "[Cpu::Clock] " << std::hex << start_pc << std::dec
              << " | instruction='" << inst_->name
              << "' - cycles=" << inst_->cycles << std::endl;
  }

  cycles_--;
}

void Cpu::Fetch() { arg_ = as_->Read(arg_addr_); }

#define SF(flag, value) r_.SetFlag(flag, value)
#define GF(flag) r_.GetFlag(flag)
#define WM(addr, value) as_->Write(addr, value)
#define RM(addr) as_->Read(addr)
#define PS(value) WM(0x0100 + r_.s--, value)

/// <editor-fold desc="Addressing Modes">
u8 Cpu::IMP() {
  arg_ = r_.a;

  return 0;
}

u8 Cpu::IMM() {
  arg_addr_ = r_.pc++;

  return 0;
}

u8 Cpu::ZP0() {
  arg_addr_ = RM(r_.pc++);
  arg_addr_ &= 0x00FF;

  return 0;
}

u8 Cpu::ABS() {
  auto lo = RM(r_.pc++);
  auto hi = RM(r_.pc++);

  arg_addr_ = (hi << 8) | lo;

  return 0;
}

u8 Cpu::REL() {
  auto offset = i8(RM(r_.pc++));

  arg_ = r_.pc + offset;

  return 0;
}

u8 Cpu::IND() {
  auto lo = RM(r_.pc++);
  auto hi = RM(r_.pc++);

  auto temp_address = (hi << 8) | lo;
  arg_addr_ = (RM(temp_address + 1) << 8) | (RM(temp_address + 0));

  return 0;
}

u8 Cpu::ZPX() {
  arg_addr_ = RM(r_.pc++);
  arg_addr_ += r_.x;
  arg_addr_ &= 0x00FF;

  return 0;
}

u8 Cpu::ZPY() {
  arg_addr_ = RM(r_.pc++);
  arg_addr_ += r_.x;
  arg_addr_ &= 0x00FF;

  return 0;
}

u8 Cpu::ABX() {
  auto lo = RM(r_.pc++);
  auto hi = RM(r_.pc++);

  arg_addr_ = ((hi << 8) | lo) + r_.x;

  // Check if hi bits changed upon addition of X.
  if ((arg_addr_ & 0xFF00) != (hi << 8))
    return 1;
  else
    return 0;
}

u8 Cpu::ABY() {
  auto lo = RM(r_.pc++);
  auto hi = RM(r_.pc++);

  arg_addr_ = ((hi << 8) | lo) + r_.y;

  // Check if hi bits changed upon addition of X.
  if ((arg_addr_ & 0xFF00) != (hi << 8))
    return 1;
  else
    return 0;
}

u8 Cpu::IZX() {
  auto address = RM(r_.pc++);

  auto lo = RM((address + r_.x) & 0xFF);
  auto hi = RM((address + 1 + r_.x) & 0xFF);

  arg_addr_ = (hi << 8) | lo;

  return 0;
}

u8 Cpu::IZY() {
  auto address = RM(r_.pc++);

  auto lo = RM(address & 0xFF);
  auto hi = RM((address + 1) & 0xFF);

  arg_addr_ = ((hi << 8) | lo) + r_.y;

  if ((arg_addr_ & 0xFF00) != (hi << 8))
    return 1;
  else
    return 0;
}
/// </editor-fold>

/// <editor-fold desc="Instructions">

u8 Cpu::ADC() {
  auto result = u16(r_.a) + u16(arg_) + u16(GF(kC));

  SF(kC, result > 255);
  SF(kZ, (result & 0x00FF) == 0);
  SF(kV, (~(u8(r_.a) ^ u16(arg_)) & (u16(r_.a) ^ u16(result))) & 0x0080);
  SF(kN, result & 0x80);

  r_.a = result & 0x00FF;

  return 1;
}

u8 Cpu::AND() {
  r_.a = r_.a & arg_;

  SF(kZ, r_.a == 0);
  SF(kN, r_.a & 0x80);

  return 1;
}

u8 Cpu::ASL() {
  auto temp = u16(arg_ << 1);

  SF(kC, (temp & 0xFF00) > 0);
  SF(kZ, (temp & 0xFF) == 0);
  SF(kN, temp & 0x80);

  if (inst_->addressing_mode_handler == &Cpu::IMP)
    r_.a = temp & 0xFF;
  else
    WM(arg_addr_, temp & 0xFF);

  return 0;
}

u8 Cpu::BCC() {
  if (GF(kC))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BCS() {
  if (!GF(kC))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BEQ() {
  if (!GF(kZ))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BIT() {
  auto temp = arg_ & r_.a;

  SF(kZ, temp == 0x00);
  SF(kN, arg_ & (1 << 7));
  SF(kV, arg_ & (1 << 6));

  return 0;
}

u8 Cpu::BMI() {
  if (!GF(kN))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BNE() {
  if (GF(kZ))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BPL() {
  if (GF(kN))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BRK() {
  r_.pc++;

  PS((r_.pc >> 8) & 0x00FF);
  PS(r_.pc & 0x00FF);

  SF(kI, true);
  SF(kB, true);

  PS(r_.p);

  SF(kB, false);

  r_.pc = u16(RM(0xFFFE)) | (u16(RM(0xFFFF)) << 8);

  return 0;
}

u8 Cpu::BVC() {
  if (GF(kV))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::BVS() {
  if (!GF(kV))
    return 0;

  cycles_++;

  if ((arg_ & 0xFF00) != (r_.pc & 0xFF))
    cycles_++;

  r_.pc = arg_;

  return 0;
}

u8 Cpu::CLC() {
  SF(kC, false);

  return 0;
}

u8 Cpu::CLD() {
  SF(kD, false);

  return 0;
}

u8 Cpu::CLI() {
  SF(kI, false);

  return 0;
}

u8 Cpu::CLV() {
  SF(kV, false);

  return 0;
}

u8 Cpu::CMP() {
  auto temp = u16(r_.a) - u16(arg_);

  SF(kC, r_.a >= arg_);
  SF(kZ, (temp & 0x00FF) == 0x00);
  SF(kN, temp & 0x80);

  return 1;
}

u8 Cpu::CPX() {
  auto temp = u16(r_.x) - u16(arg_);

  SF(kC, r_.x >= arg_);
  SF(kZ, (temp & 0x00FF) == 0x00);
  SF(kN, temp & 0x80);

  return 0;
}

u8 Cpu::CPY() {
  auto temp = u16(r_.y) - u16(arg_);

  SF(kC, r_.y >= arg_);
  SF(kZ, (temp & 0x00FF) == 0x00);
  SF(kN, temp & 0x80);

  return 0;
}

u8 Cpu::DEC() {
  auto temp = u16(arg_) - 1;
  WM(arg_addr_, temp);

  SF(kN, temp & 0x80);
  SF(kZ, (temp & 0xFF) == 0);

  return 0;
}

u8 Cpu::DEX() {
  r_.x -= 1;

  SF(kZ, r_.x == 0x00);
  SF(kN, r_.x & 0x80);

  return 0;
}

u8 Cpu::DEY() {
  r_.y -= 1;

  SF(kZ, r_.y == 0x00);
  SF(kN, r_.y & 0x80);

  return 0;
}

u8 Cpu::EOR() {
  r_.a = r_.a ^ arg_;

  SF(kZ, r_.a == 0x00);
  SF(kN, r_.a & 0x80);

  return 1;
}

u8 Cpu::INC() {
  auto temp = u16(arg_) + 1;
  WM(arg_addr_, temp);

  SF(kN, temp & 0x80);
  SF(kZ, (temp & 0xFF) == 0);

  return 0;
}

u8 Cpu::INX() {
  r_.x += 1;

  SF(kZ, r_.x == 0x00);
  SF(kN, r_.x & 0x80);

  return 0;
}

u8 Cpu::INY() {
  r_.y += 1;

  SF(kZ, r_.y == 0x00);
  SF(kN, r_.y & 0x80);

  return 0;
}

u8 Cpu::JMP() {
  r_.pc = arg_addr_;

  return 0;
}

u8 Cpu::JSR() {
  r_.pc--;

  PS((r_.pc >> 8) & 0xFF);
  PS(r_.pc & 0xFF);

  r_.pc = arg_addr_;

  return 0;
}

u8 Cpu::LDA() {
  r_.a = arg_;

  SF(kZ, r_.a == 0x00);
  SF(kN, r_.a & 0x80);

  return 0;
}

u8 Cpu::LDX() {
  r_.x = arg_;

  SF(kZ, r_.x == 0x00);
  SF(kN, r_.x & 0x80);

  return 0;
}

u8 Cpu::LDY() {
  r_.y = arg_;

  SF(kZ, r_.y == 0x00);
  SF(kN, r_.y & 0x80);

  return 0;
}

u8 Cpu::LSR() {
  auto temp = u16(arg_) >> 1;

  SF(kN, 0);
  SF(kZ, (temp & 0xFF) == 0x00);
  SF(kC, arg_ & 0x1);

  if (inst_->addressing_mode_handler == &Cpu::IMP)
    r_.a = temp & 0xFF;
  else
    WM(arg_addr_, temp & 0xFF);

  return 0;
}

u8 Cpu::NOP() {
  switch (opcode_) {
  case 0x1C:
  case 0x3C:
  case 0x5C:
  case 0x7C:
  case 0xDC:
  case 0xFC:
    return 1;
    break;
  }

  return 0;
}

u8 Cpu::ORA() {
  r_.a = r_.a | arg_;

  SF(kZ, r_.a == 0x00);
  SF(kN, r_.a & 0x80);

  return 1;
}

u8 Cpu::PHA() {
  PS(r_.a);

  return 0;
}

u8 Cpu::PHP() {
  PS(r_.p | u8(kB) | u8(kU));

  return 0;
}

u8 Cpu::PLA() { return 0; }

u8 Cpu::PLP() { return 0; }

u8 Cpu::ROL() { return 0; }

u8 Cpu::ROR() { return 0; }

u8 Cpu::RTI() { return 0; }

u8 Cpu::RTS() { return 0; }

u8 Cpu::SBC() { return 0; }

u8 Cpu::SEC() { return 0; }

u8 Cpu::SED() { return 0; }

u8 Cpu::SEI() { return 0; }

u8 Cpu::STA() { return 0; }

u8 Cpu::STX() { return 0; }

u8 Cpu::STY() { return 0; }

u8 Cpu::TAX() { return 0; }

u8 Cpu::TAY() { return 0; }

u8 Cpu::TSX() { return 0; }

u8 Cpu::TXA() { return 0; }

u8 Cpu::TXS() { return 0; }

u8 Cpu::TYA() { return 0; }

u8 Cpu::XXX() { return 0; }
/// </editor-fold>

#undef PS
#undef GF
#undef SF
#undef RM
#undef WM

} // namespace nes