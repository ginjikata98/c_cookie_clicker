cmake_minimum_required(VERSION 3.23)
project(keylistener C)

set(CMAKE_C_STANDARD 99)

FILE(GLOB SOURCE_FILES src/*.c)

add_executable(keylistener ${SOURCE_FILES})

target_link_libraries(
        ${PROJECT_NAME}
        "-framework Cocoa -framework Carbon -framework CoreServices"
)