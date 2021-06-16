//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "bus.h"

namespace nes {

Bus::Bus() : cpu_(this) {
  for (auto &i : ram_) ram_[i] = 0x00;
}

Bus::~Bus() = default;

void Bus::Write(u16 address, u8 data) {
  if (address >= 0x0000 && address <= 0xffff)
    ram_[address] = data;
}

uint8_t Bus::Read(u16 address, bool readonly) {
  if (address >= 0x0000 && address <= 0xffff)
    return ram_[address];

  return 0;
}

}