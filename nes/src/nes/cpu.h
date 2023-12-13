#ifndef NES_NES_SRC_CPU_H_
#define NES_NES_SRC_CPU_H_

#include "bus.h"
#include "types.h"

namespace nes {

struct CpuRegisters {
  u8 a;
  u8 x, y;
  u16 pc;
  u8 s;
  u8 p;
};

class Cpu {
public: /** Public API */
  Cpu();
  ~Cpu();

  u8 Read(u16 address);
  void Write(u16 address, u8 value);

  u8 Clock();

private: /** Internal API */
  /** Addressing Modes */
  u8 IMP(); u8 ACC(); u8 IMM(); u8 ZPG(); u8 ABS(); u8 REL(); u8 IND();
  u8 ZPX(); u8 ZPY(); u8 ABX(); u8 ABY(); u8 IXI(); u8 IIX();

  /** Opcodes */
  u8 ADC(); u8 AND(); u8 ASL(); u8 BCC(); u8 BCS(); u8 BEQ(); u8 BIT(); u8 BMI();
  u8 BNE(); u8 BPL(); u8 BRK(); u8 BVC(); u8 BVS(); u8 CLC(); u8 CLD(); u8 CLI();
  u8 CLV(); u8 CMP(); u8 CPX(); u8 CPY(); u8 DEC(); u8 DEX(); u8 DEY(); u8 EOR();
  u8 INC(); u8 INX(); u8 INY(); u8 JMP(); u8 JSR(); u8 LDA(); u8 LDX(); u8 LDY();
  u8 LSR(); u8 NOP(); u8 ORA(); u8 PHA(); u8 PHP(); u8 PLA(); u8 PLP(); u8 ROL();
  u8 ROR(); u8 RTI(); u8 RTS(); u8 SBC(); u8 SEC(); u8 SED(); u8 SEI(); u8 STA();
  u8 STX(); u8 STY(); u8 TAX(); u8 TAY(); u8 TSX(); u8 TXA(); u8 TXS(); u8 TYA();

  /** Invalid Opcode */
  u8 XXX();

private: /** Member Variables */
  std::shared_ptr<Bus> bus_;

  CpuRegisters r_;
};

} // namespace nes

#endif // NES_NES_SRC_CPU_H_
