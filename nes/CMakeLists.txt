#
#  Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
#

set(
        NES_SRC

        src/main.cc

        src/emulator/hardware/bus.cc src/emulator/hardware/bus.h
        src/emulator/hardware/cpu.cc src/emulator/hardware/cpu.h

        src/render/window.cc src/render/window.h
        src/render/shader.cc src/render/shader.h
        src/render/vertex_buffer.cc src/render/vertex_buffer.h
        src/render/vertex_array.cc src/render/vertex_array.h
        src/render/index_buffer.cc src/render/index_buffer.h

        src/util/types.h
)

set(
        IMGUI_SRC

        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui.h
        ${PROJECT_SOURCE_DIR}/extern/imgui/imconfig.h
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui_internal.h
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/imstb_rectpack.h
        ${PROJECT_SOURCE_DIR}/extern/imgui/imstb_textedit.h
        ${PROJECT_SOURCE_DIR}/extern/imgui/imstb_truetype.h

        ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.h

        ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.h
        src/util/event_emitter.cc src/util/event_emitter.h src/emulator/asm/assembler.cc src/emulator/asm/assembler.h)

add_executable(
        nes

        ${NES_SRC}
        ${IMGUI_SRC}
)

target_link_libraries(
        nes

        glad
        glfw
        glm
)

target_include_directories(
        nes

        PRIVATE
        ${PROJECT_SOURCE_DIR}/extern/glad/include
        ${PROJECT_SOURCE_DIR}/extern/glfw/include
        ${PROJECT_SOURCE_DIR}/extern/glm
        ${PROJECT_SOURCE_DIR}/extern/imgui
)