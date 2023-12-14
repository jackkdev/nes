set(
    NES_SRC

    src/npch.cc src/npch.h

    src/main.cc

    src/nes/types.h

    src/nes/nes.cc src/nes/nes.h
    src/nes/renderer.cc src/nes/renderer.h

    src/nes/cpu.cc src/nes/cpu.h
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

target_link_libraries(
    nes

    glfw
    glad
)

target_precompile_headers(
    nes

    PRIVATE src/npch.h
)

target_compile_definitions(
    nes

    PRIVATE GLFW_INCLUDE_NONE
)