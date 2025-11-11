cmake_minimum_required(VERSION 3.10)
project(mouse_pos C)

set(CMAKE_C_STANDARD 99)

# # Đường dẫn tuyệt đối đến thư viện
# set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libs)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs ${CMAKE_CURRENT_BINARY_DIR}/libs_build)

# Executable
add_executable(run
    mouse_pos.c
)

target_link_libraries(run
    MY_DEVICE
    MY_STRLIB
)
