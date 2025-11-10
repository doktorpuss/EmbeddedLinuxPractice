cmake_minimum_required(VERSION 3.10)
project(mouse_pos C)

set(CMAKE_C_STANDARD 99)

# Đường dẫn tuyệt đối đến thư viện
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libs)

add_library(MY_DEVICE
    ${LIBS_DIR}/my_device/my_device.c
)

target_include_directories(MY_DEVICE PUBLIC
    ${LIBS_DIR}/my_device
)

add_library(MY_STRLIB
    ${LIBS_DIR}/my_strlib/my_strlib.c
)

target_include_directories(MY_STRLIB PUBLIC
    ${LIBS_DIR}/my_strlib
)

# Executable
add_executable(run
    mouse_pos.c
)

target_link_libraries(run
    MY_DEVICE
    MY_STRLIB
)
