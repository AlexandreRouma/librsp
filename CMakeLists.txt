cmake_minimum_required(VERSION 3.13)
project(rsp)

file(GLOB_RECURSE SRC "src/*.cpp" "lib/*.c")

add_executable(rsp ${SRC})

if (MSVC)
    find_package(libusb CONFIG REQUIRED)
    target_include_directories(rsp PRIVATE ${LIBUSB_INCLUDE_DIRS} "lib/")
    target_link_libraries(rsp PRIVATE ${LIBUSB_LIBRARIES})
    message(${LIBUSB_INCLUDE_DIRS})
elseif (ANDROID)
    target_link_libraries(rsp PUBLIC
        /sdr-kit/${ANDROID_ABI}/lib/libusb1.0.so
    )
else (MSVC)
    find_package(PkgConfig)

    pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

    target_include_directories(rsp PRIVATE ${LIBUSB_INCLUDE_DIRS})
    target_link_directories(rsp PRIVATE ${LIBUSB_LIBRARY_DIRS})
    target_link_libraries(rsp PRIVATE ${LIBUSB_LIBRARIES})
endif ()