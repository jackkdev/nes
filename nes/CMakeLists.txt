set(
    NES_SRC

    src/npch.cc src/npch.h

    src/main.cc

    src/nes/types.h
    src/nes/nes.cc src/nes/nes.h

    src/nes/emulator/emulator.cc src/nes/emulator/emulator.h
    src/nes/emulator/cpu.cc src/nes/emulator/cpu.h

    src/nes/graphics/window.cc src/nes/graphics/window.h
    src/nes/graphics/renderer.cc src/nes/graphics/renderer.h
    src/nes/graphics/imgui_layer.cc
    src/nes/graphics/imgui_layer.h
)

add_executable(
    nes

    ${NES_SRC}
)

target_include_directories(
    nes

    PRIVATE

    src
)

target_link_libraries(
    nes

    glfw
    glad
    imgui
)

target_precompile_headers(
    nes

    PRIVATE src/npch.h
)

target_compile_definitions(
    nes

    PRIVATE GLFW_INCLUDE_NONE
)