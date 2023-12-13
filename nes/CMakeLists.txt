set(
    NES_SRC

    src/npch.cc src/npch.h

    src/main.cc

    src/nes/types.h

    src/nes/nes.cc src/nes/nes.h
    src/nes/cpu.cc src/nes/cpu.h
    src/nes/bus.cc
    src/nes/bus.h
)

add_executable(
    nes

    ${NES_SRC}
)

target_include_directories(
    nes

    PRIVATE

    nes
)

target_precompile_headers(
    nes

    PRIVATE src/npch.h
)