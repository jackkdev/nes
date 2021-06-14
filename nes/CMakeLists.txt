#
#  Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
#

set(
        NES_SRC

        src/main.cc

        src/hardware/bus.cc src/hardware/bus.h
        src/hardware/cpu.cc src/hardware/cpu.h

        src/render/window.cc src/render/window.h

        src/util/types.h
)

add_executable(
        nes

        ${NES_SRC}
)