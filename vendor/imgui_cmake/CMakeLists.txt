set(
    IMGUI_SRC

    ../imgui/imgui.cpp ../imgui/imgui.h
    ../imgui/imgui_draw.cpp
    ../imgui/imgui_demo.cpp
    ../imgui/imgui_widgets.cpp
    ../imgui/imgui_tables.cpp
    ../imgui/imgui_internal.h

    ../imgui/backends/imgui_impl_glfw.cpp ../imgui/backends/imgui_impl_glfw.h
    ../imgui/backends/imgui_impl_opengl3.cpp ../imgui/backends/imgui_impl_opengl3.h
)

add_library(
    imgui

    STATIC

    ${IMGUI_SRC}
)

target_include_directories(
    imgui

    PUBLIC

    ../imgui
    ../imgui/backends

    PRIVATE

    ../glfw/include
)