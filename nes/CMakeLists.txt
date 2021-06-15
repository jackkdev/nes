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
        src/render/shader.cc src/render/shader.h src/render/vertex_buffer.cc src/render/vertex_buffer.h src/render/vertex_array.cc src/render/vertex_array.h src/render/quad.cc src/render/quad.h src/render/index_buffer.cc src/render/index_buffer.h)

add_executable(
        nes

        ${NES_SRC}
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
)