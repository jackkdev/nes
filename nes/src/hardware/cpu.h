//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_CPU_H_
#define NES_NES_SRC_CPU_H_

#include "../util/types.h"

namespace nes {

class Bus;

// Represents the 6502 CPU.
class CPU {
 public: // Internal structures.
	enum Flag {
		C = (1 << 0),
		Z = (1 << 1),
		I = (1 << 2),
		D = (1 << 3),
		B = (1 << 4),
		U = (1 << 5),
		V = (1 << 6),
		N = (1 << 7),
	};

 public: // Constructor/destructor.
	explicit CPU(Bus *bus);
	~CPU();

 public: // Bus reading/writing.
	void Write(u16 address, u8 data);
	uint8_t Read(u16 address, bool readonly = false);

 private:
	Bus *bus_ = nullptr; // Bus reference.

 private: // Simple registers.
	u8 a_ = 0x00, x_ = 0x00, y_ = 0x00; // Accumulator, X, Y.
	u8 sp_ = 0x00; // Stack pointer.
	u16 pc_ = 0x0000; // Program counter.


 public: // Status register implementation.
	bool GetFlag(Flag flag) const;
	void SetFlag(Flag flag, bool value);

 private:
	u8 status_ = 0x00; // Status register.

 private: // Addressing modes.
	u8 fetched_; // Value fetched by fetch or IMP addressing mode.
	u16 fetch_address_, relative_fetch_address_; // The absolute and relative address to fetch from.

	u8 IMP(); u8 IMM();
	u8 ZP0(); u8 ZPX();
	u8 ZPY(); u8 REL();
	u8 ABS(); u8 ABX();
	u8 ABY(); u8 IND();
	u8 IZX(); u8 IZY();

 private: // Instructions.
	u8 ADC();	u8 AND();	u8 ASL();	u8 BCC();
	u8 BCS();	u8 BEQ();	u8 BIT();	u8 BMI();
	u8 BNE();	u8 BPL();	u8 BRK();	u8 BVC();
	u8 BVS();	u8 CLC();	u8 CLD();	u8 CLI();
	u8 CLV();	u8 CMP();	u8 CPX();	u8 CPY();
	u8 DEC();	u8 DEX();	u8 DEY();	u8 EOR();
	u8 INC();	u8 INX();	u8 INY();	u8 JMP();
	u8 JSR();	u8 LDA();	u8 LDX();	u8 LDY();
	u8 LSR();	u8 NOP();	u8 ORA();	u8 PHA();
	u8 PHP();	u8 PLA();	u8 PLP();	u8 ROL();
	u8 ROR();	u8 RTI();	u8 RTS();	u8 SBC();
	u8 SEC();	u8 SED();	u8 SEI();	u8 STA();
	u8 STX();	u8 STY();	u8 TAX();	u8 TAY();
	u8 TSX();	u8 TXA();	u8 TXS();	u8 TYA();

	u8 XXX();
};

}

#endif //NES_NES_SRC_CPU_H_
