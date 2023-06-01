cmake_minimum_required(VERSION 3.13)
project(rsp)

file(GLOB_RECURSE SRC "src/*.cpp" "lib/*.c")

add_executable(rsp ${SRC})

find_package(libusb CONFIG REQUIRED)
target_include_directories(rsp PRIVATE ${LIBUSB_INCLUDE_DIRS} "lib/")
target_link_libraries(rsp PRIVATE ${LIBUSB_LIBRARIES})
message(${LIBUSB_INCLUDE_DIRS})