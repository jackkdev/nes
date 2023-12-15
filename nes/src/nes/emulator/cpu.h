#ifndef NES_NES_SRC_CPU_H_
#define NES_NES_SRC_CPU_H_

#include "../types.h"

namespace nes {

typedef std::array<u8, 2048> CpuRam;

class CpuAddressSpace {
public:
  explicit CpuAddressSpace(const std::shared_ptr<CpuRam> &ram);
  ~CpuAddressSpace();

  u8 Read(u16 address);
  void Write(u16 address, u8 data);

private:
  std::shared_ptr<CpuRam> ram_;
};

enum CpuFlag : u8 {
  kC = 1,
  kZ = 1 << 1,
  kI = 1 << 2,
  kD = 1 << 3,
  kB = 1 << 4,
  kU = 1 << 5,
  kV = 1 << 6,
  kN = 1 << 7,
};

struct CpuRegisters {
  u8 a;
  u8 x, y;
  u16 pc;
  u8 s;
  u8 p;

  [[nodiscard]] bool GetFlag(CpuFlag flag) const { return (p & u8(flag)) != 0; }

  void SetFlag(CpuFlag flag, bool value) {
    if (value)
      p |= u8(flag);
    else
      p &= ~u8(flag);
  }
};

class Cpu {
public:
  struct Instruction {
    const char *name;
    u8 (Cpu::*operation_handler)();
    u8 (Cpu::*addressing_mode_handler)();
    u8 cycles;
  };

public:
  explicit Cpu();
  ~Cpu();

  void Attach(std::unique_ptr<CpuAddressSpace> as);

  [[nodiscard]] const CpuRegisters &GetRegisters() const;

  u8 Clock();

private:
  void Fetch();

private:
  // clang-format off
  /// Addressing Modes
  u8 IMP(); u8 IMM(); u8 ZP0(); u8 ABS(); u8 REL(); u8 IND();
  u8 ZPX(); u8 ZPY(); u8 ABX(); u8 ABY(); u8 IZX(); u8 IZY();

  /// Instructions
  u8 ADC(); u8 AND(); u8 ASL(); u8 BCC(); u8 BCS(); u8 BEQ(); u8 BIT(); u8 BMI();
  u8 BNE(); u8 BPL(); u8 BRK(); u8 BVC(); u8 BVS(); u8 CLC(); u8 CLD(); u8 CLI();
  u8 CLV(); u8 CMP(); u8 CPX(); u8 CPY(); u8 DEC(); u8 DEX(); u8 DEY(); u8 EOR();
  u8 INC(); u8 INX(); u8 INY(); u8 JMP(); u8 JSR(); u8 LDA(); u8 LDX(); u8 LDY();
  u8 LSR(); u8 NOP(); u8 ORA(); u8 PHA(); u8 PHP(); u8 PLA(); u8 PLP(); u8 ROL();
  u8 ROR(); u8 RTI(); u8 RTS(); u8 SBC(); u8 SEC(); u8 SED(); u8 SEI(); u8 STA();
  u8 STX(); u8 STY(); u8 TAX(); u8 TAY(); u8 TSX(); u8 TXA(); u8 TXS(); u8 TYA();

  /// Invalid Instructions
  u8 XXX();
  // clang-format on

private:
  std::unique_ptr<CpuAddressSpace> as_;
  CpuRegisters r_;
  std::vector<Instruction> lookup_;

  u8 cycles_;
  u8 opcode_;
  Instruction *inst_;
  u8 arg_;
  u16 arg_addr_;
};

} // namespace nes

#endif // NES_NES_SRC_CPU_H_
