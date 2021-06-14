//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_HARDWARE_BUS_H_
#define NES_NES_SRC_HARDWARE_BUS_H_

#include "cpu.h"
#include "../util/types.h"

#include <array>

namespace nes {

class Bus {
 public:
	Bus();
	~Bus();

 public:
	void Write(u16 address, u8 data);
	uint8_t Read(u16 address, bool readonly = false);

 private:
	CPU cpu_;
	std::array<u8, 64 * 1024> ram_ = {};
};

}

#endif //NES_NES_SRC_HARDWARE_BUS_H_
