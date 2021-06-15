set(
        GLAD_SRC

        src/gl.c

        include/glad/gl.h
        include/KHR/khrplatform.h
)

set(
        GLAD_INCLUDE

        ${PROJECT_SOURCE_DIR}/extern/glad/include
)

set(
        GLAD_LINK

        glad
)

add_library(
        glad

        STATIC
        ${GLAD_SRC}
)

target_include_directories(
        glad

        PRIVATE
        include
)