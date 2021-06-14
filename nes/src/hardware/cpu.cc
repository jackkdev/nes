//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "cpu.h"
#include "bus.h"

namespace nes {

CPU::CPU(Bus *bus) : bus_(bus) {
}

CPU::~CPU() = default;

void CPU::Write(u16 address, u8 data) {
	bus_->Write(address, data);
}

uint8_t CPU::Read(u16 address, bool readonly) {
	return bus_->Read(address, readonly);
}

bool CPU::GetFlag(CPU::Flag flag) const {
	return ((status_ & flag) > 0);
}

void CPU::SetFlag(CPU::Flag flag, bool value) {
	if (value)
		status_ |= flag;
	else
		status_ |= ~flag;
}

u8 CPU::IMP() {
	fetched_ = a_;
	return 0;
}

u8 CPU::IMM() {
	// Example:
	// ADC #$05
	// 0x69 0x05
	// The address of 0x05 is placed in fetch_address_.
	fetch_address_ = pc_++;

	return 0;
}

u8 CPU::ZP0() {
	fetch_address_ = Read(pc_++);
	fetch_address_ &= 0x00FF;

	return 0;
}

u8 CPU::ZPX() {
	fetch_address_ = Read(pc_++ + x_);
	fetch_address_ &= 0x00FF;

	return 0;
}

u8 CPU::ZPY() {
	fetch_address_ = Read(pc_++ + y_);
	fetch_address_ &= 0x00FF;

	return 0;
}

u8 CPU::REL() {
	relative_fetch_address_ = Read(pc_++);

	// Check if the value is negative.
	if (relative_fetch_address_ & 0x80)
		relative_fetch_address_ |= 0xFF00;

	return 0;
}

u8 CPU::ABS() {
	u16 lo = Read(pc_++);
	u16 hi = Read(pc_++);

	fetch_address_ = (hi << 8) | lo;

	return 0;
}

u8 CPU::ABX() {
	u16 lo = Read(pc_++);
	u16 hi = Read(pc_++);

	fetch_address_ = (hi << 8) | lo;
	fetch_address_ += x_;

	return ((fetch_address_ & 0xFF00) != (hi << 8)) ? 1 : 0;
}

u8 CPU::ABY() {
	u16 lo = Read(pc_++);
	u16 hi = Read(pc_++);

	fetch_address_ = (hi << 8) | lo;
	fetch_address_ += y_;

	return ((fetch_address_ & 0xFF00) != (hi << 8)) ? 1 : 0;
}

u8 CPU::IND() {

	return 0;
}

u8 CPU::IZX() {
	return 0;
}

u8 CPU::IZY() {
	return 0;
}

}