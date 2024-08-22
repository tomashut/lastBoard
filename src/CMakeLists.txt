cmake_minimum_required(VERSION 3.22)

project(source)
add_library(source INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)


target_include_directories(source INTERFACE
    src
)

target_sources(source INTERFACE

    basicPin.c
    basicI2C.c
    i2cConfig.c
    i2c_interface.c

)

target_link_directories(source INTERFACE
)

target_link_libraries(source INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
