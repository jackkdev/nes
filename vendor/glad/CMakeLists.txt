set(
    GLAD_SRC

    src/gl.c include/glad/gl.h
    include/KHR/khrplatform.h
)

add_library(
    glad

    STATIC

    ${GLAD_SRC}
)

target_include_directories(
    glad

    PRIVATE src
    PUBLIC include
)